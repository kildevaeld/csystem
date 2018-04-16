#include "utf8.h"
#include <csystem/string.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

size_t cs_str_indexof(const char *path, char p) {
  int len = strlen(path);
  return cs_lstr_indexof(path, len, p);
}

size_t cs_lstr_indexof(const char *path, size_t size, char p) {
  for (int i = 0; i < size; i++) {
    if (path[i] == p)
      return i;
  }
  return -1;
}

size_t cs_str_last_indexof(const char *path, char h) {
  size_t len = strlen(path);
  return cs_lstr_last_indexof(path, len, h);
}

size_t cs_lstr_last_indexof(const char *path, size_t len, char h) {
  int i = len;
  while (i >= 0) {
    if (path[--i] == h)
      return i;
  }
  return -1;
}

char *cs_str_hex(const char *str, char *hex, size_t maxlen) {
  unsigned char ch, i, j, len;

  len = strlen(str);

  if (hex == NULL) {
    hex = malloc(sizeof(char) * (len * 2) + 1);
    if (!hex)
      return NULL;
  } else if ((len * 2) > maxlen) {
    return NULL;
  }

  /*for (i = 0, j = 0; i < len; i++, j += 2) {
    ch = str[i];

    if (ch >= 0 && ch <= 0x0F) {
      hex[j] = 0x30;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x10 && ch <= 0x1F) {
      hex[j] = 0x31;
      ch -= 0x10;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x20 && ch <= 0x2F) {
      hex[j] = 0x32;
      ch -= 0x20;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x30 && ch <= 0x3F) {
      hex[j] = 0x33;
      ch -= 0x30;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x40 && ch <= 0x4F) {
      hex[j] = 0x34;
      ch -= 0x40;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x50 && ch <= 0x5F) {
      hex[j] = 0x35;
      ch -= 0x50;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x60 && ch <= 0x6F) {
      hex[j] = 0x36;
      ch -= 0x60;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    } else if (ch >= 0x70 && ch <= 0x7F) {
      hex[j] = 0x37;
      ch -= 0x70;

      if (ch >= 0 && ch <= 9)
        hex[j + 1] = 0x30 + ch;
      else
        hex[j + 1] = 0x37 + ch;
    }
  }
  printf("J %i\n", j);
  hex[j] = 0x00;*/
  /*for (int i = 0, j = 0; i < len; i++, j += 2) {
    char res[2];
    itoa((str[i] & 0xFF), res, 16);
    if (res[1] == 0) {
      hex[j] = 0x30;
      hex[j + 1] = res[0];
    } else {
      hex[j] = res[0];
      hex[j + 1] = res[1];
    }
  }*/
  // Null-Terminating the string with converted buffer
  hex[(len * 2)] = '\0';

  return hex;
}

char *cs_str_hex_str(const char *str, char *hex, size_t maxlen) {
  int len = strlen(str);

  if (hex == NULL) {
    hex = malloc(sizeof(char) * (len * 2) + 1);
    if (!hex)
      return NULL;
  } else if ((len * 2) > maxlen) {
    return NULL;
  }
  char *tmp = hex;
  while (*str) {
    sprintf(tmp, "%02x", *str++);
    tmp = tmp + 2;
  }
  return hex;
}

#define CS_STR_BLOCK_SIZE 9

typedef struct cs_string_t {
  char *data;
  size_t len;
  size_t alloc;
} cs_string_t;

static bool alloc_atleast(cs_string_t *str, size_t len);

cs_string_t *cs_str_alloc() {
  cs_string_t *str = (cs_string_t *)malloc(sizeof(cs_string_t));
  if (!str)
    return NULL;

  str->data = malloc(sizeof(char) * CS_STR_BLOCK_SIZE);
  str->alloc = CS_STR_BLOCK_SIZE;
  str->len = 0;

  return str;
}

void cs_str_free(cs_string_t *str) {
  if (!str)
    return;

  free(str->data);
  str->data = NULL;
  free(str);
}

static bool alloc_atleast(cs_string_t *str, size_t len) {
  int i = ceil(len / CS_STR_BLOCK_SIZE);
  int nsize = i * CS_STR_BLOCK_SIZE;

  char *data = realloc(str->data, nsize);
  if (!data) {
    return false;
  }
  str->data = data;
  str->alloc = nsize;

  return true;
}

void cs_str_append(cs_string_t *str, const char *s) {

  size_t len = strlen(s);
  size_t nlen = len + str->len;

  if (nlen >= str->alloc) {
    if (!alloc_atleast(str, nlen)) {
      return;
    }
  }

  memcpy(str->data + str->len, s, len);
  str->len = nlen;
}

void cs_str_append_char(cs_string_t *str, char c) {
  size_t nlen = 1 + str->len;

  if (nlen >= str->alloc) {
    if (!alloc_atleast(str, nlen)) {
      return;
    }
  }
  str->data[str->len] = c;
  str->len++;
}

void cs_str_appendf(cs_string_t *str, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char *out;
  if (vasprintf(&out, fmt, args) == -1) {
    return;
  }
  va_end(args);
  cs_str_append(str, out);
  free(out);
}

void cs_str_insert(cs_string_t *str, size_t idx, const char *s) {
  if (idx > str->len) {
    return;
  }
  if (idx == str->len) {
    cs_str_append(str, s);
    return;
  }

  int len = strlen(s);
  int nlen = str->len + len;

  if (nlen >= str->alloc) {
    if (!alloc_atleast(str, nlen)) {
      return;
    }
  }

  int l = str->len - idx;
  char tmp[l];
  memcpy(tmp, str->data + idx, l);
  memcpy(str->data + idx, s, len);
  memcpy(str->data + idx + len, tmp, l);
  str->len = nlen;
}

void cs_str_insert_char(cs_string_t *str, size_t idx, char c) {
  int nlen = str->len + 1;
  if (nlen >= str->alloc) {
    if (!alloc_atleast(str, nlen)) {
      return;
    }
  }

  if (idx >= str->len) {
    cs_str_append_char(str, c);
  } else {
    int l = str->len - idx;
    char tmp[l];
    memcpy(tmp, str->data + idx, l);
    str->data[idx] = c;
    memcpy(str->data + idx + 1, tmp, l);
    str->len = nlen;
  }
}

char cs_str_index_get(cs_string_t *str, size_t idx) {
  if (idx >= str->len)
    return -1;
  return str->data[idx];
}

void cs_str_index_set(cs_string_t *str, size_t idx, char c) {
  if (idx >= str->len)
    return;
  str->data[idx] = c;
}

void cs_str_remove(cs_string_t *str, size_t idx, size_t len) {
  if (idx + len >= str->len) {
    str->len = idx;
    return;
  }
  char *ptr = idx > 0 ? str->data + idx : str->data;
  memcpy(ptr, str->data + (idx) + len, str->len - (idx + len));
  str->len -= len;
}

void cs_str_clear(cs_string_t *str) {
  str->len = 0;
  memset(str->data, 0, str->alloc);
}
void cs_str_compact(cs_string_t *str) {
  int len = str->len;
  if (0 == len) {
    len = CS_STR_BLOCK_SIZE;
  }
  alloc_atleast(str, len);
}

size_t cs_str_len(cs_string_t *str) { return str->len; }

size_t cs_str_allocs(cs_string_t *str) { return str->alloc; }

void cs_str_copy(cs_string_t *str, char *buf) {
  memcpy(buf, str->data, str->len);
}

char *cs_str_string(cs_string_t *str) {
  char *out = malloc(sizeof(char) * str->len + 1);
  cs_str_copy(str, out);
  out[str->len] = '\0';
  return out;
}

static int utf_width(char c) {
  if (CS_IS_UTF8_2C(c))
    return 2;
  else if (CS_IS_UTF8_3C(c))
    return 3;
  else if (CS_IS_UTF8_4C(c))
    return 4;
  return 1;
}

void cs_str_utf8_append(cs_string_t *str, const char *buf) {
  if (utf8valid(buf)) {
    return;
  }
  cs_str_append(str, buf);
}
void cs_str_utf8_appendf(cs_string_t *str, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char *out;
  if (vasprintf(&out, fmt, args) == -1) {
    return;
  }
  va_end(args);
  cs_str_utf8_append(str, out);
  free(out);
}

static size_t find_index(cs_string_t *str, size_t idx) {
  size_t i = 0;
  while (i < str->len) {
    if (i == idx)
      return i;
    if (CS_IS_UTF(str->data[i])) {
      i += utf_width(str->data[i]);
    } else {
      i++;
    }

    if (i >= idx)
      return i;
  }
  return -1;
}

int cs_str_utf8_insert(cs_string_t *str, size_t idx, const char *buf) {
  if (utf8valid(buf)) {
    return 0;
  }

  size_t u8len = cs_str_utf8_len(str);

  if (idx > u8len) {
    return 0;
  } else if (idx == u8len) {
    cs_str_append(str, buf);
    return u8len;
  } else if (idx == 0) {
    cs_str_insert(str, 0, buf);
    return u8len;
  }

  size_t i = find_index(str, idx);
  cs_str_insert(str, i, buf);

  return u8len;
}

int cs_str_utf8_insert_char(cs_string_t *str, size_t idx, char c) {

  size_t len = cs_str_utf8_len(str);

  if (idx > len) {
    return 0;
  } else if (idx == len) {
    cs_str_append_char(str, c);
    return 1;
  } else if (idx == 0) {
    cs_str_insert_char(str, 0, c);
    return 1;
  }

  size_t i = find_index(str, idx);
  cs_str_insert_char(str, i, c);

  return 1;
}

int cs_str_utf8_remove(cs_string_t *str, size_t idx, size_t len) {
  if (idx >= str->len)
    return 0;

  if (idx != 0) {
    idx = find_index(str, idx);
  }

  size_t eidx = find_index(str, idx + len);
  size_t nlen = eidx - idx;
  cs_str_remove(str, idx, nlen);

  return 1;
}

size_t cs_str_utf8_len(cs_string_t *str) {
  size_t length = 0;
  size_t i = 0;
  while (i < str->len) {
    if (CS_IS_UTF(str->data[i])) {
      i += utf_width(str->data[i]);
    } else {
      i++;
    }
    length++;
  }

  return length;
}