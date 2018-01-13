#include <csystem/features.h>
#include <csystem/path.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static int normalize(const char *segment, int strip_first, int *idx) {
  int x_len = strlen(segment);
  int i = 0;
  if (x_len == 0)
    return 0;

  if (segment[0] == CS_PATH_SEPARATOR && strip_first) {
    ++i;
    --x_len;
  }
  if (x_len > 2 && segment[x_len - 1] == CS_PATH_SEPARATOR) {
    --x_len;
  }
  // if (x_len <= 0)
  // return 0;

  *idx = i;
  return x_len;
}

/*static int resolve(const char *buffer, char *path, int *buf_len) {
  int i = 0;
  int len = 0;
  for (;;) {
    if (strncmp(path, "..", 2)) {
      break;
    }

    *buf_len = cs_path_dir(buffer);

    // int len = cs_path_dir(buffer);

    path = path + 2;
    int l = 0, idx = 0;
    if (!(l = normalize(path, 0, &idx))) {
      continue;
    }
    len += l;
    path = path + idx;

    if (!memcpy(buffer + (*buf_len)++, '/', 1))
      return 0;

    if (!memcpy(buffer, path + idx, len))
      return 0;

    i = (*buf_len) +

    // if (!memcpy(buffer, path))
  }
  return i;
}*/

int cs_path_join(char *buffer, const char **paths) {

  int len = 0;
  while (*paths) {
    const char *x = *paths++;

    int x_len, idx;
    if (!(x_len = normalize(x, len != 0, &idx))) {
      continue;
    }

    if (len != 0) {

      /*if (strncmp(x + idx, "..", 2) == 0) {
      }*/

      // Add separator
      if (buffer[len - 1] != CS_PATH_SEPARATOR)
        if (!memcpy(buffer + len++, "/", 1)) {
          return 0;
        }
    }
    if (!memcpy(buffer + len, x + idx, x_len)) {
      return 0;
    }
    len += x_len;
  }

  buffer[len] = '\0';

  return len;
}

int cs_path_base(const char *path, int *idx) {
  int strl = strlen(path);
  int counter = strl;
  int len = strl;
  *idx = 0;
  while (counter-- >= 0) {
    if (path[counter] == CS_PATH_SEPARATOR) {
      *idx = counter + 1;
      len = strl - *idx;
      break;
    }
  }
  return len;
}

int cs_path_dir(const char *path) {
  int len = strlen(path);
  for (int i = 0; i < len; i++) {
    if (i != 0 && path[i] == CS_PATH_SEPARATOR) {
      return i;
    }
  }
  return 0;
}

int cs_path_ext(const char *path, int *idx) {
  int _idx;
  int len = cs_path_base(path, &_idx);
  if (len == 0)
    return 0;
  char *p = path + _idx;
  for (int i = 0; i < len; i++) {
    if (i != 0 && p[i] == '.') {
      *idx = _idx + i;
      break;
    }
  }
  return len - (*idx);
}

char *cs_path_resolve(char *buffer, char *path) { return NULL; }