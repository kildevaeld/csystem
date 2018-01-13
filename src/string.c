#include <csystem/string.h>
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
  while (--len) {
    if (path[len] == h)
      return len;
  }
  return -1;
}