#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int cs_home_dir(char *buf);
int cs_config_dir(char *buf);
int cs_temp_dir(char *buf);
int cs_data_dir(char *buf);
int cs_cache_dir(char *buffer);

#ifdef __cplusplus
}
#endif