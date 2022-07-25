#ifndef UTIL_H
#define UTIL_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace util {
inline void ltrim(std::string &str) noexcept {
  str.erase(str.begin(),
            std::find_if(str.begin(), str.end(),
                         [](unsigned char c) { return !std::isspace(c); }));
}

inline void rtrim(std::string &str) noexcept {
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](unsigned char c) { return !std::isspace(c); })
                .base(),
            str.end());
}

inline void trim(std::string &str) noexcept {
  ltrim(str);
  rtrim(str);
}

inline void strtolower(std::string &str) noexcept {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

inline bool isint(const std::string &s) noexcept {
  std::string::const_iterator it{s.begin()};
  while (it != s.end() && std::isdigit(*it))
    ++it;

  return !s.empty() && it == s.end();
}

inline std::vector<std::string> split(const std::string &s) {
  std::stringstream ss(s);
  std::vector<std::string> words;
  for (std::string w; ss >> w;)
    words.push_back(w);
  return words;
}
} // namespace util
#endif // UTIL_H
