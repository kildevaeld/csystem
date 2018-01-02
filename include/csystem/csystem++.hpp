#pragma once
#include <csystem/features.h>
#include <initializer_list>
#include <string>

namespace csystem {

namespace standardpaths {

std::string home();
std::string config();
std::string data();
std::string cache();
std::string tmpdir();

} // namespace standardpaths

namespace path {

std::string join(std::initializer_list<std::string> &&args);

template <typename... T> std::string join(T &&... a) {
  return join({std::forward<T>(a)...});
}

#if defined(CS_HAS_CPP_17)
std::string_view basename(const std::string &path);
std::string_view dirname(const std::string &path);
#else
std::string basename(const std::string &path);
std::string dirname(const std::string &path);
#endif

} // namespace path

} // namespace csystem