#include "view_options.h"

#include <f0_claude_remote_icons.h>

#include "view_plate.h"

static void view_options_draw_plate(Canvas* canvas) {
    view_plate_draw_outline(canvas, 63, 0, 64);
    view_plate_draw_fill(canvas, 63, 0, 36);
    view_plate_draw_white_icon(canvas, 66, 2, &I_back);
    view_plate_draw_white_str(canvas, 77, 9, "EXIT");
    canvas_draw_str(canvas, 101, 9, "BACK");
}

static void view_options_draw_row(Canvas* canvas, bool vibration) {
    canvas_draw_str(canvas, 5, 26, "Vibration");
    canvas_draw_str_aligned(canvas, 102, 26, AlignCenter, AlignBottom, vibration ? "On" : "Off");
}

static void view_options_draw_cursor(Canvas* canvas) {
    canvas_draw_rframe(canvas, 1, 16, 125, 13, 2);
    canvas_draw_icon(canvas, 80, 19, &I_left);
    canvas_draw_icon(canvas, 120, 19, &I_right);
}

void view_options_draw(Canvas* canvas, bool vibration) {
    canvas_set_font(canvas, FontSecondary);
    view_options_draw_plate(canvas);
    view_options_draw_row(canvas, vibration);
    view_options_draw_cursor(canvas);
}
