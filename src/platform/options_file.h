#pragma once

#include <stdbool.h>

typedef struct OptionsFile OptionsFile;

OptionsFile* options_file_alloc(bool vibration);

void options_file_free(OptionsFile* options_file);

bool options_file_vibration(const OptionsFile* options_file);

void options_file_set_vibration(OptionsFile* options_file, bool vibration);
