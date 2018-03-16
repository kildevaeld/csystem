#pragma once
#include <stdlib.h>

size_t cs_str_indexof(const char *path, char p);
size_t cs_lstr_indexof(const char *path, size_t size, char p);

size_t cs_str_last_indexof(const char *path, char h);
size_t cs_lstr_last_indexof(const char *path, size_t size, char h);

char *cs_str_hex(const char *str, char *hex, size_t maxlen);

char *cs_str_hex_str(const char *str, char *hex, size_t maxlen);