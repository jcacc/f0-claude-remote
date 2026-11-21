#pragma once
/*
 * ESP32 port (Sor3nt Flipper-Zero-ESP32-Port) compatibility layer.
 *
 * The port's firmware API table does not export furi_event_loop_*, the thread
 * signal callback, nor message-queue counts, so a FAP that calls them refuses
 * to load. This header remaps the subset this app uses onto a small polling
 * loop built from exported primitives (FuriMessageQueue + FuriTimer).
 *
 * Semantics kept: every callback (queue and timer) runs on the thread that
 * called furi_event_loop_run, so the app's single-thread assumptions hold.
 */
#include <furi.h>

FuriMessageQueue* compat_queue_alloc(uint32_t count, uint32_t size);
void compat_queue_free(FuriMessageQueue* queue);
void compat_queue_reset(FuriMessageQueue* queue);

FuriEventLoop* compat_loop_alloc(void);
void compat_loop_free(FuriEventLoop* loop);
void compat_loop_run(FuriEventLoop* loop);
void compat_loop_stop(FuriEventLoop* loop);
void compat_loop_subscribe_queue(
    FuriEventLoop* loop,
    FuriMessageQueue* queue,
    FuriEventLoopEvent event,
    FuriEventLoopEventCallback callback,
    void* context);
void compat_loop_unsubscribe(FuriEventLoop* loop, FuriEventLoopObject* object);

FuriEventLoopTimer* compat_timer_alloc(
    FuriEventLoop* loop,
    FuriEventLoopTimerCallback callback,
    FuriEventLoopTimerType type,
    void* context);
void compat_timer_free(FuriEventLoopTimer* timer);
void compat_timer_start(FuriEventLoopTimer* timer, uint32_t interval);
void compat_timer_stop(FuriEventLoopTimer* timer);

#define furi_message_queue_alloc                compat_queue_alloc
#define furi_message_queue_free                 compat_queue_free
#define furi_message_queue_reset                compat_queue_reset
#define furi_event_loop_alloc                   compat_loop_alloc
#define furi_event_loop_free                    compat_loop_free
#define furi_event_loop_run                     compat_loop_run
#define furi_event_loop_stop                    compat_loop_stop
#define furi_event_loop_subscribe_message_queue compat_loop_subscribe_queue
#define furi_event_loop_unsubscribe             compat_loop_unsubscribe
#define furi_event_loop_timer_alloc             compat_timer_alloc
#define furi_event_loop_timer_free              compat_timer_free
#define furi_event_loop_timer_start             compat_timer_start
#define furi_event_loop_timer_stop              compat_timer_stop

/* No loader exit signal on the port; the app closes via its own Exit action. */
#define furi_thread_set_signal_callback(thread, cb, ctx) ((void)0)
