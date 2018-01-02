#pragma once

#define CS_PATH_SEPARATOR '/'

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Concat 1 or more path together into buffer.
 * @params {char *} buffer
 * @params {char **} paths
 * @return {int}
 */
int cs_path_join(char *buffer, const char **paths);
int cs_path_base(const char *path, int *idx);
int cs_path_dir(const char *path);
char *cs_path_resolve(char *buffer, char *paths);


#ifdef __cplusplus
}
#endif