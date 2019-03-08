#include <csystem/csystem++.hpp>
#include <csystem/csystem.h>
#include <iostream>
#include <memory>

namespace csystem {

namespace path {

std::string join(std::initializer_list<std::string> &&args) {
  const char *arguments[args.size() + 1];
  int i = 0;
  int size = 0;
  for (const auto &a : args) {
    arguments[i++] = a.c_str();
    size = a.size() + 1;
  }
  arguments[i] = NULL;
  char buffer[size + 10];
  int len;

  char *data = cs_path_join_array(NULL, arguments);
  if (!data)
    return "";

  std::string path(data);
  free(data);
  return data;
}

#if defined(CS_HAS_CPP_17)
std::string_view basename(const std::string &path) {
#else
std::string basename(const std::string &path) {
#endif
  int idx, len;
  if (!(len = cs_path_base(path.c_str(), &idx)))
#if defined(CS_HAS_CPP_17)
    return std::string_view("");
#else
    return std::string("");
#endif

  return path.substr(idx, len);
}

#if defined(CS_HAS_CPP_17)
std::string_view dirname(const std::string &path) {
#else
std::string dirname(const std::string &path) {
#endif
  int len;
  if (!(len = cs_path_dir(path.c_str())))
#if defined(CS_HAS_CPP_17)
    return std::string_view("");
#else
    return std::string("");
#endif
  return path.substr(0, len);
}

} // namespace path

} // namespace csystem