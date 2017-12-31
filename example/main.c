#include <csystem/csystem.h>
#include <stdio.h>

int main() {

  char buf[256];
  cs_home_dir(buf);
  printf("homedir %s\n", buf);
  cs_config_dir(buf);
  printf("config %s\n", buf);
  cs_temp_dir(buf);
  printf("temp %s\n", buf);
  cs_data_dir(buf);
  printf("data %s\n", buf);

  cs_path_join(buf, (const char *[]){"Hello/", "/world", NULL});
  printf("buf: %s\n", buf);

  int index;
  char *path = "/test/png.js";
  int len = cs_path_base(path, &index);
  printf("base %s\n", path + index);

  len = cs_path_dir(path);
  char out[len];
  strncpy(out, path, len);
  printf("dir %s\n", out);

  return 0;
}