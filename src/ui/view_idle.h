#pragma once

#include <gui/canvas.h>

#include "../core/action.h"

void view_idle_draw(Canvas* canvas, Action flash, bool legend, uint8_t charge, bool charging);
