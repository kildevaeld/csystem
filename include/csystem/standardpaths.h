#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  cs_stdpath_user_domain,
  cs_stdpath_local_domain
} cs_stdpath_domain;

typedef enum {
  cs_stdpath_config_dir,
  cs_stdpath_data_dir,
  cs_stdpath_cache_dir
} cs_stdpath_dir;

char *cs_getcwd(char *buffer, size_t maxlen);
char *cs_gethomedir(char *buffer, size_t maxlen);
char *cs_getconfigdir(char *buffer, size_t maxlen);
char *cs_getdatadir(char *buffer, size_t maxlen);
char *cs_getcachedir(char *buffer, size_t maxlen);
char *cs_gettmpdir(char *buffer, size_t maxlen);

char *cs_path_for_dir(cs_stdpath_dir dir, cs_stdpath_domain domain);

#ifdef __cplusplus
}
#endif