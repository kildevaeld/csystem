#pragma once

#include "features.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

int home_dir(char *buf);
int config_dir(char *buf);
int temp_dir(char *buf);
int data_dir(char *buf);
int cache_dir(char *buffer);

int app_data_dir(char *buffer, const char *app_name);

#ifdef __cplusplus
}
#endif