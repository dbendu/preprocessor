#pragma once

#include "stddef.h"
#include "string.h"

char* substr(const char* str, size_t len);
void strrep(char* replaceable_str, size_t symbols, const char* src, size_t copy_symbols_count);