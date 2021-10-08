#include "stdlib.h"
#include "memory.h"

#include "str.h"

char* substr(const char* src, size_t len)
{
    char* substring = malloc(len + 1);

    memcpy(substring, src, len);
    substring[len] = '\0';

    return substring;
}

void strrep(char* replaceable_str, size_t symbols, const char* src, size_t copy_symbols_count)
{
    if (copy_symbols_count > symbols)
        memmove(replaceable_str + copy_symbols_count,
                replaceable_str + symbols,
                strlen(replaceable_str) - symbols);
    else if (copy_symbols_count < symbols)
        memmove(replaceable_str + symbols - copy_symbols_count,
                replaceable_str + symbols,
                strlen(replaceable_str) - symbols);

    memmove(replaceable_str, src, copy_symbols_count);
}