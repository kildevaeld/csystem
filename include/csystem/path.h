#pragma once

#define CS_PATH_SEPARATOR '/'

int cs_path_join(char *buffer, const char **paths);
int cs_path_base(const char *path, int *idx);
int cs_path_dir(const char *path);