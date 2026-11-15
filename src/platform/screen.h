#pragma once

#include <furi.h>

#include "../core/action.h"
#include "../core/link.h"
#include "../core/mode.h"
#include "../core/option.h"

typedef struct Screen Screen;

Screen* screen_alloc(
    FuriEventLoop* event_loop,
    FuriMessageQueue* input_queue,
    Mode mode,
    Link link,
    bool legend);

void screen_free(Screen* screen);

void screen_set_mode(Screen* screen, Mode mode);

void screen_set_link(Screen* screen, Link link);

void screen_set_legend(Screen* screen, bool legend);

void screen_set_charge(Screen* screen, uint8_t charge);

void screen_set_charging(Screen* screen, bool charging);

void screen_set_option(Screen* screen, Option option, bool on);

void screen_set_cursor(Screen* screen, Option cursor);

void screen_flash(Screen* screen, Action action, uint32_t duration_ms);
