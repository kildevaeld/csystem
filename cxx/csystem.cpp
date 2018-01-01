#include <csystem/csystem++.hpp>
#include <csystem/csystem.h>
#include <iostream>

namespace csystem {

namespace standardpaths {

std::string home() {
  std::unique_ptr<char[]> buffer(cs_gethomedir(NULL, 0));
  return std::string(buffer.get());
}

std::string config() {
  std::unique_ptr<char[]> buffer(cs_getconfigdir(NULL, 0));
  return std::string(buffer.get());
}
std::string data() {
  std::unique_ptr<char[]> buffer(cs_getdatadir(NULL, 0));
  return std::string(buffer.get());
}
std::string cache() {
  std::unique_ptr<char[]> buffer(cs_getcachedir(NULL, 0));
  return std::string(buffer.get());
}

} // namespace standardpaths

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
  char buffer[size];
  int len;
  if (!(len = cs_path_join(buffer, arguments)))
    return std::string("");

  return std::string(buffer, len);
}

std::string_view basename(const std::string &path) {
  int idx, len;
  if (!(len = cs_path_base(path.c_str(), &idx)))
    return std::string_view("");

  return path.substr(idx, len);
}

std::string_view dirname(const std::string &path) {
  int len;
  if (!(len = cs_path_dir(path.c_str())))
    return std::string_view("");

  return path.substr(0, len);
}

} // namespace path

} // namespace csystem