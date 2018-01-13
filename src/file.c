#include <csystem/file.h>
#include <stdio.h>
#include <stdlib.h>

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
}

char *cs_read_file(const char *filename, char *buffer) {
  buffer = NULL;
  int string_size, read_size;
  FILE *handler = fopen(filename, "r");

  if (handler) {
    // Seek the last byte of the file
    fseek(handler, 0, SEEK_END);
    // Offset from the first to the last byte, or in other words, filesize
    string_size = ftell(handler);
    // go back to the start of the file
    rewind(handler);

    // Allocate a string that can hold it all
    buffer = (char *)malloc(sizeof(char) * (string_size + 1));

    // Read it all in one operation
    read_size = fread(buffer, sizeof(char), string_size, handler);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[string_size] = '\0';

    if (string_size != read_size) {
      // Something went wrong, throw away the memory and set
      // the buffer to NULL
      free(buffer);
      buffer = NULL;
    }

    // Always remember to close the file.
    fclose(handler);
  }

  return buffer;
}