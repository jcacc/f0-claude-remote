#pragma once

#include <gui/canvas.h>

#include "../core/option.h"

void view_options_draw(Canvas* canvas, const bool options[OptionMAX], Option cursor);
