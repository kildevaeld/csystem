#include <csystem/csystem++.hpp>
#include <csystem/csystem.h>
#include <iostream>
#include <memory>

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

std::string tmpdir() {
  std::unique_ptr<char[]> buffer(cs_gettmpdir(NULL, 0));
  return std::string(buffer.get());
}

std::string cwd() {
  std::unique_ptr<char[]> buffer(cs_getcwd(NULL, 0));
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