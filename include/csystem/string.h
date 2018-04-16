#pragma once
#include <stdlib.h>

size_t cs_str_indexof(const char *path, char p);
size_t cs_lstr_indexof(const char *path, size_t size, char p);

size_t cs_str_last_indexof(const char *path, char h);
size_t cs_lstr_last_indexof(const char *path, size_t size, char h);

char *cs_str_hex(const char *str, char *hex, size_t maxlen);

char *cs_str_hex_str(const char *str, char *hex, size_t maxlen);

typedef struct cs_string_t cs_string_t;

cs_string_t *cs_str_alloc();
void cs_str_free(cs_string_t *);
void cs_str_append(cs_string_t *, const char *);
void cs_str_appendf(cs_string_t *, const char *fmt, ...);
void cs_str_append_char(cs_string_t *, char);
void cs_str_insert(cs_string_t *, size_t idx, const char *);
void cs_str_insert_char(cs_string_t *, size_t idx, char);

void cs_str_remove(cs_string_t *, size_t idx, size_t len);
void cs_str_clear(cs_string_t *);
void cs_str_compact(cs_string_t *);
size_t cs_str_len(cs_string_t *);
size_t cs_str_allocs(cs_string_t *);
void cs_str_copy(cs_string_t *, char *buf);
char *cs_str_string(cs_string_t *);
