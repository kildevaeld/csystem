#pragma once

int cs_file_size(const char *filename);
char *cs_read_file(const char *filename, char *buffer, size_t maxlen,
                   size_t *len);