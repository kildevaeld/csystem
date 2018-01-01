#include <csystem/features.h>
#include <csystem/standardpaths.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#if defined(CS_PLATFORM_UNIX)
#include <pwd.h>
#include <unistd.h>
#elif defined(CS_PLATFORM_WINDOWS)
#include <direct.h>
#endif

#define CS_LINUX_GEN(ENV, DEFALUT)                                             \
  char *config = from_env(ENV), buffer, maxlen);                               \
  if (!config && errno == ERR_NOT_FOUND) {                                     \
    config = append_home(buffer, maxlen, DEAFULT, sizeof(DEFAULT));            \
  }                                                                            \
  return config;

#define CS_DARWIN_GEN(PATH)                                                    \
  return append_home(buffer, maxlen, PATH, sizeof(PATH));

#define ERR_NOT_FOUND 5040

static size_t home_len() {
  char *dir = getenv("HOME");
  struct passwd *pw;
  if (!dir) {
    uid_t uid = getuid();
    pw = getpwuid(uid);

    if (pw == NULL) {
      return -1;
    }
    dir = pw->pw_dir;
  }

  return strlen(dir);
}

static char *from_env(const char *name, char *buffer, size_t maxlen) {
  char *config = getenv(name);
  if (!config) {
    errno = ERR_NOT_FOUND;
    return NULL;
  }

  size_t len = strlen(config);

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

  return strcpy(buffer, config);
}

static char *append_home(char *buffer, size_t maxlen, const char *path,
                         size_t size) {

  size_t hlen = home_len();
  size_t len = hlen + size;
  int c = 0;

  if ((buffer && len > maxlen) || (maxlen != 0 && len > maxlen))
    if (len > maxlen) {
      errno = ERANGE;
      return NULL;
    }

  if (buffer == NULL) {
    buffer = malloc(len + 1);
    if (!buffer)
      return NULL;
    c = 1;
  }

  if (!(buffer = cs_gethomedir(buffer, len))) {
    goto clean;
  }

  if (!memcpy(buffer + hlen, path, size)) {
    goto clean;
  }

  buffer[len] = '\0';

  return buffer;

clean:
  if (c)
    free(buffer);
  return NULL;
}

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

char *cs_getconfigdir(char *buffer, size_t maxlen) {
#if defined(CS_PLATFORM_LINUX)
  CS_LINUX_GEN("XDG_CONFIG_HOME", "/.config")
#elif defined(CS_PLATFORM_DARWIN)
  CS_DARWIN_GEN("/Library/Preferences")
#endif
}

char *cs_getdatadir(char *buffer, size_t maxlen) {
#if defined(CS_PLATFORM_LINUX)
  CS_LINUX_GEN("XDG_DATA_HOME", "/.local/share");
#elif defined(CS_PLATFORM_DARWIN)
  CS_DARWIN_GEN("/Library/Application Support")
#endif
}

char *cs_getcachedir(char *buffer, size_t maxlen) {
#if defined(CS_PLATFORM_LINUX)
  CS_LINUX_GEN("XDG_CACHE_HOME", "/.cache");
#elif defined(CS_PLATFORM_DARWIN)
  CS_DARWIN_GEN("/Library/Caches")
#endif
}

char *cs_gettmpdir(char *buffer, size_t maxlen) {
#if defined(CS_PLATFORM_UNIX)
  if (!(buffer = from_env("TMPDIR", buffer, maxlen)) && errno == ERR_NOT_FOUND)
    if (!(buffer = from_env("TEMP", buffer, maxlen)) && errno == ERR_NOT_FOUND)
      if (!(buffer = from_env("TMP", buffer, maxlen)) && errno == ERR_NOT_FOUND)
        return NULL;

  return buffer;

#endif

  return NULL;
}

#undef CS_LINUX_GEN
#undef CS_DARWIN_GEN