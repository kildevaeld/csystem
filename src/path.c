#include <csystem/features.h>
#include <csystem/path.h>
#include <csystem/string.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static int normalize(const char *segment, int strip_first, int *idx) {
  int c_ln = 0;
  if (segment == NULL || (c_ln = strlen(segment)) == 0)
    return 0;

  int i = 0;
  while (segment[i] == CS_PATH_SEPARATOR && i < c_ln)
    i++;

  if (!strip_first && segment[0] == CS_PATH_SEPARATOR)
    i--;

  *idx = i;

  if (segment[c_ln - 1] == CS_PATH_SEPARATOR) {
    int l = c_ln;
    while (segment[--l] == CS_PATH_SEPARATOR && l > 0)
      c_ln--;
  }

  return c_ln - i;
}

static char *resolve(const char *buffer, size_t size, const char *path,
                     int *idx, int *cidx) {
  size_t ln = size;
  size_t i = 0;
  while (strncmp(path + i, "../", 3) == 0 && ln > 0) {
    i += 3;
    ln -= 3;
    int i = cs_lstr_last_indexof(buffer, ln, CS_PATH_SEPARATOR);
    if (i) {
      ln = i + 1;
    }
  }
  *idx = ln;
  *cidx = strlen(path) - i;
  return path + i;
}

char *cs_path_join(char *buffer, ...) {
  va_list ap;
  int c_ln = 0, c_idx = 0, i = 0, ln = 0, c = 0;

  if (buffer == NULL) {
    buffer = malloc(sizeof(char) * PATH_MAX);
    c = 1;
  }
  char *current = NULL;
  va_start(ap, buffer);
  while ((current = va_arg(ap, char *))) {
    c_ln = normalize(current, i++ > 0 ? 1 : 0, &c_idx);
    // Empty string
    if (!c_ln)
      continue;
    else if (ln + c_ln >= PATH_MAX) {
      errno = EFBIG;
      goto fail;
    } else if (!ln) {
      memcpy(buffer + ln, current + c_idx, c_ln);
    } else if (strncmp(current + c_idx, "..", 2) == 0) {
      current = resolve(buffer, ln, current + c_idx, &ln, &c_ln);
      memcpy(buffer + ln, current + c_idx, c_ln);
    } else {
      memcpy(ln == 0 ? buffer : buffer + (ln++), "/", 1);
      memcpy(buffer + ln, current + c_idx, c_ln);
    }

    ln += c_ln;
  }

  buffer[ln] = '\0';

  va_end(ap);

  return buffer;

fail:
  va_end(ap);
  if (c)
    free(buffer);
  return NULL;
}

char *cs_path_join_array(char *buffer, const char **paths) {
  int c_ln = 0, c_idx = 0, i = 0, ln = 0, c = 0;

  if (buffer == NULL) {
    buffer = malloc(sizeof(char) * PATH_MAX);
    c = 1;
  }

  while (*paths) {
    const char *current = *paths++;
    c_ln = normalize(current, i++ > 0 ? 1 : 0, &c_idx);
    // Empty string
    if (!c_ln)
      continue;
    else if (ln + c_ln >= PATH_MAX) {
      errno = EFBIG;
      goto fail;
    } else if (!ln) {
      memcpy(buffer + ln, current + c_idx, c_ln);
    } else if (strncmp(current + c_idx, "..", 2) == 0) {
      current = resolve(buffer, ln, current + c_idx, &ln, &c_ln);
      memcpy(buffer + ln, current + c_idx, c_ln);
    } else {
      memcpy(ln == 0 ? buffer : buffer + (ln++), "/", 1);
      memcpy(buffer + ln, current + c_idx, c_ln);
    }

    ln += c_ln;
  }

  buffer[ln] = '\0';

  return buffer;

fail:
  if (c)
    free(buffer);
  return NULL;
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