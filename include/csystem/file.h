#pragma once

int cs_file_exists(const char *filename);
int cs_file_size(const char *filename);
char *cs_read_file(const char *filename, char *buffer, int maxlen, int *len);
int cs_write_file(const char *filename, const char *buffer, size_t len);