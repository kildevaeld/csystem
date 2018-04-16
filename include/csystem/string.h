#pragma once
#include <stdlib.h>

size_t cs_str_indexof(const char *path, char p);
size_t cs_lstr_indexof(const char *path, size_t size, char p);

size_t cs_str_last_indexof(const char *path, char h);
size_t cs_lstr_last_indexof(const char *path, size_t size, char h);

char *cs_str_hex(const char *str, char *hex, size_t maxlen);

char *cs_str_hex_str(const char *str, char *hex, size_t maxlen);

#define CS_IS_UTF8_4C(k) (0xf0 == (0xf8 & (k)))
#define CS_IS_UTF8_3C(k) (0xe0 == (0xf0 & (k)))
#define CS_IS_UTF8_2C(k) (0xc0 == (0xe0 & (k)))
#define CS_IS_UTF(k) (CS_IS_UTF8_4C(k) || CS_IS_UTF8_3C(k) || CS_IS_UTF8_2C(k))

typedef struct cs_string_t cs_string_t;

cs_string_t *cs_str_alloc();
void cs_str_free(cs_string_t *);
// Appending
void cs_str_append(cs_string_t *, const char *);
void cs_str_appendf(cs_string_t *, const char *fmt, ...);
void cs_str_append_char(cs_string_t *, char);
void cs_str_insert(cs_string_t *, size_t idx, const char *);
void cs_str_insert_char(cs_string_t *, size_t idx, char);
void cs_str_index_set(cs_string_t *str, size_t idx, char c);
// Get
char cs_str_index_get(cs_string_t *str, size_t idx);
void cs_str_copy(cs_string_t *, char *buf);
char *cs_str_string(cs_string_t *);
// Remove
void cs_str_remove(cs_string_t *, size_t idx, size_t len);
void cs_str_clear(cs_string_t *);
void cs_str_compact(cs_string_t *);
// Stats
size_t cs_str_len(cs_string_t *);
size_t cs_str_allocs(cs_string_t *);
// UTF-8
void cs_str_utf8_append(cs_string_t *, const char *);
void cs_str_utf8_appendf(cs_string_t *, const char *fmt, ...);
int cs_str_utf8_insert(cs_string_t *, size_t idx, const char *);
int cs_str_utf8_insert_char(cs_string_t *, size_t idx, char);
int cs_str_utf8_remove(cs_string_t *, size_t idx, size_t len);
size_t cs_str_utf8_len(cs_string_t *);
