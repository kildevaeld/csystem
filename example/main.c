#include <csystem/home.h>
#include <stdio.h>

int main() {

  char buf[256];
  home_dir(buf);
  printf("homedir %s\n", buf);
  config_dir(buf);
  printf("config %s\n", buf);
  temp_dir(buf);
  printf("temp %s\n", buf);
  app_data_dir(buf, "blueprint");
  printf("app %s\n", buf);

  return 0;
}