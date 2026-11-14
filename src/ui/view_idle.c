#include "view_idle.h"

#include <f0_claude_remote_icons.h>

#include "view_plate.h"

static void view_idle_draw_legend(Canvas* canvas) {
    canvas_set_font(canvas, FontSecondary);
    view_plate_draw_outline(canvas, 74, 0, 53);
    view_plate_draw_fill(canvas, 74, 0, 30);
    view_plate_draw_white_str(canvas, 77, 9, "HOLD");
    canvas_draw_str(canvas, 106, 9, "TAP");
}

static void view_idle_draw_ring(Canvas* canvas) {
    /* Comes first: an icon paints its whole box, the clear cells too. */
    canvas_draw_icon(canvas, 38, 15, &I_recess);
    view_plate_draw_outline(canvas, 3, 14, 65);
    view_plate_draw_fill(canvas, 3, 14, 53);
    view_plate_draw_white_icon(canvas, 6, 15, &I_slash);
    view_plate_draw_white_str(canvas, 10, 22, "effort high");
    canvas_draw_icon(canvas, 58, 17, &I_up);
    view_plate_draw_outline(canvas, 2, 52, 66);
    view_plate_draw_fill(canvas, 2, 52, 54);
    view_plate_draw_white_icon(canvas, 5, 54, &I_slash);
    view_plate_draw_white_str(canvas, 9, 61, "effort max");
    canvas_draw_icon(canvas, 58, 55, &I_down);
}

/* The canvas fills no triangle, so both halves of the diagonal go row by row. */
static void view_idle_draw_ok_button(Canvas* canvas) {
    canvas_draw_rframe(canvas, 46, 28, 30, 21, 2);
    for(int32_t y = 29; y <= 47; y++) {
        canvas_draw_line(canvas, 47, y, 101 - y, y);
    }
    view_plate_draw_white_icon(canvas, 49, 30, &I_microphone_9x13);
    canvas_draw_icon(canvas, 64, 39, &I_enter);
}

static void view_idle_draw_side_actions(Canvas* canvas) {
    view_plate_draw_outline(canvas, 3, 33, 40);
    view_plate_draw_fill(canvas, 3, 33, 31);
    view_plate_draw_white_icon(canvas, 6, 35, &I_slash);
    view_plate_draw_white_str(canvas, 10, 42, "clear");
    canvas_draw_icon(canvas, 36, 35, &I_left);
    view_plate_draw_outline(canvas, 80, 33, 30);
    view_plate_draw_fill(canvas, 89, 33, 21);
    canvas_draw_icon(canvas, 83, 35, &I_right);
    view_plate_draw_white_str(canvas, 92, 42, "Esc");
    view_plate_draw_outline(canvas, 78, 46, 45);
    view_plate_draw_fill(canvas, 78, 46, 33);
    view_plate_draw_white_icon(canvas, 81, 48, &I_back);
    view_plate_draw_white_str(canvas, 92, 55, "exit");
    canvas_draw_icon(canvas, 113, 48, &I_options);
}

static void view_idle_draw_flash(Canvas* canvas, Action flash) {
    canvas_set_color(canvas, ColorXOR);
    switch(flash) {
    case ActionArrowUp:
        canvas_draw_box(canvas, 56, 15, 11, 9);
        break;
    case ActionArrowDown:
        canvas_draw_box(canvas, 56, 53, 11, 9);
        break;
    case ActionArrowLeft:
        canvas_draw_box(canvas, 34, 34, 8, 9);
        break;
    case ActionArrowRight:
        canvas_draw_box(canvas, 81, 34, 8, 9);
        break;
    case ActionEnter:
        for(int32_t y = 29; y <= 47; y++) {
            canvas_draw_line(canvas, 102 - y, y, 74, y);
        }
        break;
    case ActionEffortHigh:
        canvas_draw_box(canvas, 4, 15, 51, 9);
        break;
    case ActionEffortMax:
        canvas_draw_box(canvas, 3, 53, 52, 9);
        break;
    case ActionClear:
        canvas_draw_box(canvas, 4, 34, 29, 9);
        break;
    case ActionEsc:
        canvas_draw_box(canvas, 90, 34, 19, 9);
        break;
    case ActionNone:
    case ActionVoiceStart:
    case ActionVoiceStop:
    case ActionExit:
    case ActionGiveUp:
    case ActionStartOver:
        break;
    }
    canvas_set_color(canvas, ColorBlack);
}

void view_idle_draw(Canvas* canvas, Action flash) {
    view_idle_draw_legend(canvas);
    view_idle_draw_ring(canvas);
    view_idle_draw_ok_button(canvas);
    view_idle_draw_side_actions(canvas);
    view_idle_draw_flash(canvas, flash);
}
