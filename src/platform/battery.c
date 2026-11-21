#include "battery.h"

#include <furi_hal_power.h>

/* ESP32 port: the power service's pubsub and power_get_info are not exported to
 * FAPs, so the charge is polled from the fuel-gauge capacity calls instead.
 * Charging state is not exposed at all, so it always reads as not charging. */

#define BATTERY_POLL_MS 30000

struct Battery {
    FuriTimer* timer;
    FuriMessageQueue* charge_queue;
    FuriMessageQueue* charging_queue;
    uint8_t last_charge;
};

static uint8_t battery_charge(void) {
    uint32_t full = furi_hal_power_get_battery_full_capacity();
    uint32_t remaining = furi_hal_power_get_battery_remaining_capacity();
    if(full == 0) return 100;
    uint32_t pct = remaining * 100 / full;
    return pct > 100 ? 100 : (uint8_t)pct;
}

/* Runs on the timer thread; a queue put is thread-safe. */
static void battery_poll(void* context) {
    Battery* battery = context;
    uint8_t charge = battery_charge();
    if(charge != battery->last_charge) {
        battery->last_charge = charge;
        furi_message_queue_put(battery->charge_queue, &charge, 0);
    }
}

Battery* battery_alloc(FuriMessageQueue* charge_queue, FuriMessageQueue* charging_queue) {
    Battery* battery = malloc(sizeof(Battery));
    battery->charge_queue = charge_queue;
    battery->charging_queue = charging_queue;
    battery->last_charge = battery_charge();
    furi_message_queue_put(charge_queue, &battery->last_charge, 0);
    bool charging = false;
    furi_message_queue_put(charging_queue, &charging, 0);
    battery->timer = furi_timer_alloc(battery_poll, FuriTimerTypePeriodic, battery);
    furi_timer_start(battery->timer, furi_ms_to_ticks(BATTERY_POLL_MS));
    return battery;
}

void battery_free(Battery* battery) {
    furi_timer_stop(battery->timer);
    furi_timer_free(battery->timer);
    free(battery);
}
