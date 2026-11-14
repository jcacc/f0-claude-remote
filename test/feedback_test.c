#include "feedback.h"
#include "test.h"

static void test_sent_actions_vibrate(void) {
    assert(feedback_vibrates(ActionEnter, true));
    assert(feedback_vibrates(ActionArrowUp, true));
    assert(feedback_vibrates(ActionArrowDown, true));
    assert(feedback_vibrates(ActionArrowLeft, true));
    assert(feedback_vibrates(ActionArrowRight, true));
    assert(feedback_vibrates(ActionEsc, true));
    assert(feedback_vibrates(ActionEffortHigh, true));
    assert(feedback_vibrates(ActionEffortMax, true));
    assert(feedback_vibrates(ActionClear, true));
    assert(feedback_vibrates(ActionVoiceStart, true));
}

static void test_the_rest_stay_silent(void) {
    assert(!feedback_vibrates(ActionNone, true));
    assert(!feedback_vibrates(ActionVoiceStop, true));
    assert(!feedback_vibrates(ActionExit, true));
    assert(!feedback_vibrates(ActionGiveUp, true));
    assert(!feedback_vibrates(ActionStartOver, true));
}

static void test_nothing_vibrates_with_vibration_off(void) {
    assert(!feedback_vibrates(ActionNone, false));
    assert(!feedback_vibrates(ActionEnter, false));
    assert(!feedback_vibrates(ActionArrowUp, false));
    assert(!feedback_vibrates(ActionArrowDown, false));
    assert(!feedback_vibrates(ActionArrowLeft, false));
    assert(!feedback_vibrates(ActionArrowRight, false));
    assert(!feedback_vibrates(ActionEsc, false));
    assert(!feedback_vibrates(ActionEffortHigh, false));
    assert(!feedback_vibrates(ActionEffortMax, false));
    assert(!feedback_vibrates(ActionClear, false));
    assert(!feedback_vibrates(ActionVoiceStart, false));
    assert(!feedback_vibrates(ActionVoiceStop, false));
    assert(!feedback_vibrates(ActionExit, false));
    assert(!feedback_vibrates(ActionGiveUp, false));
    assert(!feedback_vibrates(ActionStartOver, false));
}

static void test_arrows_flash_for_100_ms(void) {
    assert(feedback_flash_ms(ActionArrowUp) == 100);
    assert(feedback_flash_ms(ActionArrowDown) == 100);
    assert(feedback_flash_ms(ActionArrowLeft) == 100);
    assert(feedback_flash_ms(ActionArrowRight) == 100);
}

static void test_enter_and_commands_flash_for_400_ms(void) {
    assert(feedback_flash_ms(ActionEnter) == 400);
    assert(feedback_flash_ms(ActionEsc) == 400);
    assert(feedback_flash_ms(ActionEffortHigh) == 400);
    assert(feedback_flash_ms(ActionEffortMax) == 400);
    assert(feedback_flash_ms(ActionClear) == 400);
}

static void test_the_rest_do_not_flash(void) {
    assert(feedback_flash_ms(ActionNone) == 0);
    assert(feedback_flash_ms(ActionVoiceStart) == 0);
    assert(feedback_flash_ms(ActionVoiceStop) == 0);
    assert(feedback_flash_ms(ActionExit) == 0);
    assert(feedback_flash_ms(ActionGiveUp) == 0);
    assert(feedback_flash_ms(ActionStartOver) == 0);
}

int main(void) {
    test_run(test_sent_actions_vibrate);
    test_run(test_the_rest_stay_silent);
    test_run(test_nothing_vibrates_with_vibration_off);
    test_run(test_arrows_flash_for_100_ms);
    test_run(test_enter_and_commands_flash_for_400_ms);
    test_run(test_the_rest_do_not_flash);
    return 0;
}
