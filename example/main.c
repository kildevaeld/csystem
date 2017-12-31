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

  return 0;
}