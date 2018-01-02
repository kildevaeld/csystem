#include <csystem/csystem++.hpp>
#include <csystem/csystem.h>
#include <csystem/features.h>
#include <iostream>
/*#include <stdio.h>

#include <stdlib.h>
#include <string.h>*/

#include <cstdio>
#include <cstdlib>

int main() {

  char *home = cs_gethomedir(NULL, 0);
  printf("homedir %s\n", home);
  free(home);
  // LEAKS
  printf("configdir %s\n", cs_getconfigdir(NULL, 0));
  printf("datadir %s\n", cs_getdatadir(NULL, 0));
  printf("temodir %s\n", cs_gettmpdir(NULL, 0));

  std::cout << csystem::standardpaths::home() << std::endl;

  std::cout << csystem::path::join("/rapper", "workd/", "/test/") << std::endl;

  std::string path = "/rapper/von/dumba";

  std::cout << csystem::path::basename(path) << std::endl;
  std::cout << csystem::path::dirname(path) << std::endl;

  std::cout << csystem::standardpaths::config() << std::endl;

  std::cout << "platform " << cs_platform_name() << std::endl;
  ;

  return 0;
}