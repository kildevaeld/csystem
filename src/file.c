#include <csystem/features.h>
#include <csystem/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*#if defined(CS_PLATFORM_UNIX)
#include <sys/stat.h>
#endif

int cs_file_stat(const char *path) {
  int string_size = -1;
  FILE *handler = fopen(path, "r");

  if (handler) {
    // Seek the last byte of the file
    fseek(handler, 0, SEEK_END);
    // Offset from the first to the last byte, or in other words, filesize
    string_size = ftell(handler);
    // Always remember to close the file.
    fclose(handler);
  }

  return string_size;
}*/

int cs_file_exists(const char *filename) {
  struct stat buffer;
  return (stat(filename, &buffer) == 0) ? 1 : 0;
}

int cs_file_size(const char *filename) {
  int string_size = -1;
  FILE *handler = fopen(filename, "r");

  if (handler) {
    // Seek the last byte of the file
    fseek(handler, 0, SEEK_END);
    // Offset from the first to the last byte, or in other words, filesize
    string_size = ftell(handler);
    // Always remember to close the file.
    fclose(handler);
  }

  return string_size;
}
char *cs_read_file(const char *filename, char *buffer, int maxlen, int *len) {
  buffer = NULL;
  int c = 0;
  int string_size, read_size;
  FILE *handler = fopen(filename, "r");

  if (!handler) {
    return NULL;
  }

  // Seek the last byte of the file
  fseek(handler, 0, SEEK_END);
  // Offset from the first to the last byte, or in other words, filesize
  string_size = ftell(handler);
  // go back to the start of the file
  rewind(handler);

  if (buffer == NULL) {
    // Allocate a string that can hold it all
    buffer = (char *)malloc(sizeof(char) * (string_size));
    c = 1;
  } else if (string_size > maxlen) {
    return NULL;
  }

  // Read it all in one operation
  read_size = fread(buffer, sizeof(char), string_size, handler);

  // fread doesn't set it so put a \0 in the last position
  // and buffer is now officially a string
  // buffer[string_size] = '\0';

  if (string_size != read_size) {
    // Something went wrong, throw away the memory and set
    // the buffer to NULL
    if (c)
      free(buffer);
    buffer = NULL;
  }

  // Always remember to close the file.
  fclose(handler);

  if (len != NULL)
    *len = string_size;

  return buffer;
}