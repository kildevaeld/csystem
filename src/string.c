#include <csystem/string.h>

size_t cs_str_indexof(const char *path, char p) {
  int len = strlen(path);
  for (int i = 0; i < len; i++) {
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