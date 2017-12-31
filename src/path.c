#include <csystem/path.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int cs_path_join(char *buffer, const char **paths) {

  int len = 0;

  while (*paths) {
    const char *x = *paths++;
    int x_len = strlen(x);
    if (x_len == 0)
      continue;
    if (x[0] == CS_PATH_SEPARATOR && len != 0) {
      ++x;
      --x_len;
    }
    if (x_len > 2 && x[x_len - 1] == CS_PATH_SEPARATOR) {
      --x_len;
    }
    if (len != 0) {
      if (!memcpy(buffer + len++, "/", 1)) {
        return 0;
      }
    }
    if (!memcpy(buffer + len, x, x_len)) {
      return 0;
    }
    len += x_len;
  }

  return len;
}