#pragma once
#include <initializer_list>
#include <string>

namespace csystem {

namespace standardpaths {

std::string home();
std::string config();
std::string data();
std::string cache();

} // namespace standardpaths

namespace path {

std::string join(std::initializer_list<std::string> &&args);

template <typename... T> std::string join(T &&... a) {
  return join({std::forward<T>(a)...});
}

std::string_view basename(const std::string &path);
std::string_view dirname(const std::string &path);

} // namespace path

} // namespace csystem