#include <csystem/csystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // LEAKS
  printf("homedir %s\n", cs_gethomedir(NULL, 0));
  printf("configdir %s\n", cs_getconfigdir(NULL, 0));
  printf("datadir %s\n", cs_getdatadir(NULL, 0));
  printf("temodir %s\n", cs_gettmpdir(NULL, 0));
  return 0;
}