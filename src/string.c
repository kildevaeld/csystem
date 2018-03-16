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

char *cs_str_hex(const char *str, char *hex, size_t maxlen) {
  unsigned char ch, i, j, len;

  len = strlen(str);

  if (hex == NULL) {
    hex = malloc(sizeof(char) * (len * 2) + 1);
    if (!hex)
      return NULL;
  } else if ((len * 2) > maxlen) {
    printf("MAX\n");
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