#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

char *cs_getcwd(char *buffer, size_t maxlen);
char *cs_gethomedir(char *buffer, size_t maxlen);

int cs_home_dir(char *buffer);
int cs_config_dir(char *buffer);
int cs_temp_dir(char *buffer);
int cs_data_dir(char *buffer);
int cs_cache_dir(char *buffer);

#ifdef __cplusplus
}
#endif