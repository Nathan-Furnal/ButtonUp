#ifndef UTIL_H
#define UTIL_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
/**
 * A utiliy header to manipulate and sanitize user input.
 */
namespace util {
/**
 * @brief ltrim, trims the common spaces from a string, starting left to right.
 * @param str, the string to trim.
 */
inline void ltrim(std::string &str) noexcept {
  str.erase(str.begin(),
            std::find_if(str.begin(), str.end(),
                         [](unsigned char c) { return !std::isspace(c); }));
}
/**
 * @brief rtrim, trims the common spaces from a string, starting from right to
 * left (in practice it does from left to right and reverses the string).
 * @param str, the string to trim.
 */
inline void rtrim(std::string &str) noexcept {
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](unsigned char c) { return !std::isspace(c); })
                .base(),
            str.end());
}
/**
 * @brief trim, trims the common spaces from a string, on either side of the
 * string.
 * @param str, the string to trim.
 */
inline void trim(std::string &str) noexcept {
  ltrim(str);
  rtrim(str);
}
/**
 * @brief strtolower, makes every (alpha)character of a string into its lower
 * version.
 * @param str, the string to lowercase.
 */
inline void strtolower(std::string &str) noexcept {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}
/**
 * @brief isint, checks is a given string such as "1" or "123" is an integer, it
 * does so by iterating over the string and checking that each character is a
 * digit.
 * @param s, the input string to check.
 * @return true if the string is an integer (representation), false otherwise.
 */
inline bool isint(const std::string &s) noexcept {
  std::string::const_iterator it{s.begin()};
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}
/**
 * @brief split, splits a string on whitespaces and returns a vector of each
 * split component.
 * @param s, the string to split.
 * @return a vector of strings, with the whitespaces removed.
 */
inline std::vector<std::string> split(const std::string &s) {
  std::stringstream ss(s);
  std::vector<std::string> words;
  for (std::string w; ss >> w;)
    words.push_back(w);
  return words;
}
} // namespace util
#endif // UTIL_H
