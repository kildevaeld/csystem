#include <csystem/features.h>
#include <csystem/standardpaths.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <errno.h>

#if defined(CS_PLATFORM_UNIX)
#include <unistd.h>
#elif defined(CS_PLATFORM_WINDOWS)
#include <direct.h>
#endif

char *cs_getcwd(char *buffer, size_t maxlen) {
#if defined CS_PLATFORM_UNIX
  return getcwd(buffer, maxlen);
#elif
  return _getcwd(buffer, maxlen);
#endif
  return NULL;
}

char *cs_gethomedir(char *buffer, size_t maxlen) {

  char *dir = getenv("HOME");
  struct passwd *pw;
  if (!dir) {
    uid_t uid = getuid();
    pw = getpwuid(uid);

    if (pw == NULL) {
      return NULL;
    }
    dir = pw->pw_dir;
  }

  size_t len = strlen(dir);

  if ((buffer && len > maxlen) || (maxlen != 0 && len > maxlen))
    if (len > maxlen) {
      errno = ERANGE;
      return NULL;
    }

  if (!buffer) {
    buffer = (char *)malloc(len + 1);
    if (!buffer)
      return NULL;
  }

  return strcpy(buffer, dir);
}

int cs_home_dir(char *buf) {

  char *dir = getenv("HOME");

  if (dir) {
    strcpy(buf, dir);
    return strlen(dir);
  }

  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (pw == NULL) {
    return 0;
  }

  if (strcpy(buf, pw->pw_dir)) {
    return strlen(pw->pw_dir);
  }

  return 0;
}

static int append_home(char *buffer, const char *path, size_t size) {
  int len = 0;
  if (!(len = cs_home_dir(buffer))) {
    return 0;
  }
  if (!memcpy(buffer + len, path, size)) {
    return 0;
  }
  return len + size;
}

static char *append_home2(char *buffer, size_t maxlen, const char *path,
                          size_t size) {

  if (!(buffer = cs_gethomedir(buffer, maxlen))) {
    return NULL;
  }

  size_t len = strlen(buffer);

  /*int len = 0;
  if (!(len = cs_home_dir(buffer))) {
    return 0;
  }
  if (!memcpy(buffer + len, path, size)) {
    return 0;
  }
  return len + size;*/
}

int cs_config_dir(char *buffer) {
  char *data = NULL;
#if defined(CS_PLATFORM_LINUX)
  char *config = getenv("XDG_CONFIG_HOME");
  if (config) {
    strcpy(buffer, config);
    return strlen(config);
  }
  return append_home(buffer, "/.config", 8);
#elif defined(CS_PLATFORM_DARWIN)
  return append_home(buffer, "/Library/Preferences", 20);
#endif

  return 0;
}

int cs_temp_dir(char *buffer) {

#if defined(CS_PLATFORM_UNIX)
  char *tmpDir = getenv("TMPDIR");
  if (!tmpDir) {
    if (!(tmpDir = getenv("TEMP")))
      if (!(tmpDir = getenv("TMP")))
        return 0;
  }
  strcpy(buffer, tmpDir);
  return strlen(tmpDir);

#endif

  return 0;
}

int cs_data_dir(char *buffer) {
  char *data = NULL;
#if defined(CS_PLATFORM_LINUX)
  char *config = getenv("XDG_DATA_HOME");
  if (config) {
    strcpy(buffer, config);
    return strlen(config);
  }
  return append_home(buffer, "/.local/share", 13);
#elif defined(CS_PLATFORM_DARWIN)
  return append_home(buffer, "/Library/Application Support", 28);
#endif
  return 0;
}

int cs_cache_dir(char *buffer) {
  char *data = NULL;
#if defined(CS_PLATFORM_LINUX)
  char *config = getenv("XDG_CACHE_HOME");
  if (config) {
    strcpy(buffer, config);
    return strlen(config);
  }
  return append_home(buffer, "/.cache", 7);
#elif defined(CS_PLATFORM_DARWIN)
  return append_home(buffer, "/Library/Caches", 15);
#endif
  return 0;
}

int cs_app_data_dir(char *buffer, const char *app_name) {
  int len = 0;
  if (!(len = cs_data_dir(buffer))) {
    return 0;
  }
  buffer[len] = '/';
  strcpy(buffer + len + 1, app_name);
  return len + strlen(app_name);
}