#include "display.h"

bool display_lit(Mode mode) {
    switch(mode) {
    case ModeIdle:
    case ModeVoice:
    case ModeOptions:
    case ModeNoLink:
    case ModeVoiceCut:
    case ModeOptionsNoLink:
        return true;
    case ModeStopped:
        break;
    }
    return false;
}
