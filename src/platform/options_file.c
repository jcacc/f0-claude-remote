#include "options_file.h"

#include <flipper_format/flipper_format.h>
#include <furi.h>
#include <storage/storage.h>

static const char* const options_file_path = APP_DATA_PATH("options.txt");
static const char* const options_file_type = "Claude Remote Options";
static const uint32_t options_file_version = 1;
static const char* const options_file_vibration_key = "Vibration";

struct OptionsFile {
    Storage* storage;
    bool vibration;
};

/* A failed read leaves its argument by the sources alone (flipper_format_stream.c:353), so the
 * value is taken only where the read answers true. The file is closed whatever the open answered
 * (storage.h:80). */
OptionsFile* options_file_alloc(bool vibration) {
    OptionsFile* options_file = malloc(sizeof(OptionsFile));
    options_file->storage = furi_record_open(RECORD_STORAGE);
    options_file->vibration = vibration;

    FlipperFormat* format = flipper_format_file_alloc(options_file->storage);
    FuriString* type = furi_string_alloc();
    uint32_t version = 0;
    bool saved = false;
    if(flipper_format_file_open_existing(format, options_file_path) &&
       flipper_format_read_header(format, type, &version) &&
       furi_string_equal_str(type, options_file_type) && version == options_file_version &&
       flipper_format_read_bool(format, options_file_vibration_key, &saved, 1)) {
        options_file->vibration = saved;
    }
    furi_string_free(type);
    flipper_format_file_close(format);
    flipper_format_free(format);
    return options_file;
}

void options_file_free(OptionsFile* options_file) {
    furi_record_close(RECORD_STORAGE);
    free(options_file);
}

bool options_file_vibration(const OptionsFile* options_file) {
    return options_file->vibration;
}

/* Held before the write, which gets one attempt: held after it, a write cut short would leave the
 * card with no value, and a change back would meet the held one and write nothing. */
void options_file_set_vibration(OptionsFile* options_file, bool vibration) {
    if(vibration == options_file->vibration) {
        return;
    }
    options_file->vibration = vibration;

    FlipperFormat* format = flipper_format_file_alloc(options_file->storage);
    if(flipper_format_file_open_always(format, options_file_path) &&
       flipper_format_write_header_cstr(format, options_file_type, options_file_version)) {
        flipper_format_write_bool(format, options_file_vibration_key, &vibration, 1);
    }
    flipper_format_file_close(format);
    flipper_format_free(format);
}
