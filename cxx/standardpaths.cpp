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

} // namespace csystem