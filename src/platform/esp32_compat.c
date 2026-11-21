/* See esp32_compat.h. This file deliberately does not include it, so the real
 * furi_message_queue_* / furi_timer_* names are used here. */
#include <furi.h>
#include <string.h>

#define COMPAT_MAX_QUEUES 16
#define COMPAT_MAX_SUBS   8
#define COMPAT_MAX_TIMERS 8
#define COMPAT_MAX_ITEM   64
#define COMPAT_IDLE_MS    10

typedef struct {
    FuriMessageQueue* queue;
    uint32_t size;
} QueueInfo;

static QueueInfo queue_infos[COMPAT_MAX_QUEUES];

static uint32_t queue_item_size(FuriMessageQueue* queue) {
    for(size_t i = 0; i < COMPAT_MAX_QUEUES; i++) {
        if(queue_infos[i].queue == queue) return queue_infos[i].size;
    }
    furi_crash("compat: unknown queue");
}

FuriMessageQueue* compat_queue_alloc(uint32_t count, uint32_t size) {
    furi_check(size <= COMPAT_MAX_ITEM);
    FuriMessageQueue* queue = furi_message_queue_alloc(count, size);
    for(size_t i = 0; i < COMPAT_MAX_QUEUES; i++) {
        if(!queue_infos[i].queue) {
            queue_infos[i].queue = queue;
            queue_infos[i].size = size;
            return queue;
        }
    }
    furi_crash("compat: too many queues");
}

/* furi_message_queue_reset is not exported by port 2.0.0: drain instead. */
void compat_queue_reset(FuriMessageQueue* queue) {
    uint8_t item[COMPAT_MAX_ITEM];
    furi_check(queue_item_size(queue) <= COMPAT_MAX_ITEM);
    while(furi_message_queue_get(queue, item, 0) == FuriStatusOk) {
    }
}

void compat_queue_free(FuriMessageQueue* queue) {
    for(size_t i = 0; i < COMPAT_MAX_QUEUES; i++) {
        if(queue_infos[i].queue == queue) queue_infos[i].queue = NULL;
    }
    furi_message_queue_free(queue);
}

typedef struct {
    FuriMessageQueue* queue; /* producers put here */
    FuriMessageQueue* staging; /* one item, handed to the callback to get from */
    FuriEventLoopEventCallback callback;
    void* context;
} Sub;

struct FuriEventLoopTimer {
    FuriEventLoop* loop;
    FuriTimer* timer;
    FuriEventLoopTimerCallback callback;
    void* context;
    volatile bool pending;
};

struct FuriEventLoop {
    Sub subs[COMPAT_MAX_SUBS];
    FuriEventLoopTimer* timers[COMPAT_MAX_TIMERS];
    volatile bool stop;
};

FuriEventLoop* compat_loop_alloc(void) {
    FuriEventLoop* loop = malloc(sizeof(FuriEventLoop));
    memset(loop, 0, sizeof(FuriEventLoop));
    return loop;
}

void compat_loop_free(FuriEventLoop* loop) {
    free(loop);
}

void compat_loop_subscribe_queue(
    FuriEventLoop* loop,
    FuriMessageQueue* queue,
    FuriEventLoopEvent event,
    FuriEventLoopEventCallback callback,
    void* context) {
    UNUSED(event);
    for(size_t i = 0; i < COMPAT_MAX_SUBS; i++) {
        Sub* sub = &loop->subs[i];
        if(!sub->queue) {
            sub->staging = furi_message_queue_alloc(1, queue_item_size(queue));
            sub->callback = callback;
            sub->context = context;
            sub->queue = queue;
            return;
        }
    }
    furi_crash("compat: too many subscriptions");
}

void compat_loop_unsubscribe(FuriEventLoop* loop, FuriEventLoopObject* object) {
    for(size_t i = 0; i < COMPAT_MAX_SUBS; i++) {
        Sub* sub = &loop->subs[i];
        if(sub->queue == object) {
            furi_message_queue_free(sub->staging);
            memset(sub, 0, sizeof(Sub));
        }
    }
}

void compat_loop_stop(FuriEventLoop* loop) {
    loop->stop = true;
}

void compat_loop_run(FuriEventLoop* loop) {
    uint8_t item[COMPAT_MAX_ITEM];
    loop->stop = false;
    while(!loop->stop) {
        bool busy = false;
        for(size_t i = 0; i < COMPAT_MAX_SUBS && !loop->stop; i++) {
            Sub* sub = &loop->subs[i];
            if(!sub->queue) continue;
            if(furi_message_queue_get(sub->queue, item, 0) == FuriStatusOk) {
                furi_message_queue_put(sub->staging, item, 0);
                sub->callback(sub->staging, sub->context);
                /* A callback that ignored its item must not wedge the next one.
                 * (furi_message_queue_reset is not exported by port 2.0.0.) */
                while(furi_message_queue_get(sub->staging, item, 0) == FuriStatusOk) {
                }
                busy = true;
            }
        }
        for(size_t i = 0; i < COMPAT_MAX_TIMERS && !loop->stop; i++) {
            FuriEventLoopTimer* timer = loop->timers[i];
            if(timer && timer->pending) {
                timer->pending = false;
                timer->callback(timer->context);
                busy = true;
            }
        }
        if(!busy) furi_delay_ms(COMPAT_IDLE_MS);
    }
}

/* Runs on the timer service thread: only flag it, the loop thread calls back. */
static void compat_timer_fired(void* context) {
    FuriEventLoopTimer* timer = context;
    timer->pending = true;
}

FuriEventLoopTimer* compat_timer_alloc(
    FuriEventLoop* loop,
    FuriEventLoopTimerCallback callback,
    FuriEventLoopTimerType type,
    void* context) {
    FuriEventLoopTimer* timer = malloc(sizeof(FuriEventLoopTimer));
    timer->loop = loop;
    timer->callback = callback;
    timer->context = context;
    timer->pending = false;
    timer->timer = furi_timer_alloc(
        compat_timer_fired,
        type == FuriEventLoopTimerTypePeriodic ? FuriTimerTypePeriodic : FuriTimerTypeOnce,
        timer);
    for(size_t i = 0; i < COMPAT_MAX_TIMERS; i++) {
        if(!loop->timers[i]) {
            loop->timers[i] = timer;
            return timer;
        }
    }
    furi_crash("compat: too many timers");
}

void compat_timer_free(FuriEventLoopTimer* timer) {
    furi_timer_stop(timer->timer);
    furi_timer_free(timer->timer);
    for(size_t i = 0; i < COMPAT_MAX_TIMERS; i++) {
        if(timer->loop->timers[i] == timer) timer->loop->timers[i] = NULL;
    }
    free(timer);
}

void compat_timer_start(FuriEventLoopTimer* timer, uint32_t interval) {
    timer->pending = false;
    furi_timer_start(timer->timer, interval);
}

void compat_timer_stop(FuriEventLoopTimer* timer) {
    furi_timer_stop(timer->timer);
    timer->pending = false;
}
