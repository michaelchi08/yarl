#include "yarl/utils/string.hpp"

namespace yarl {

std::string strim(const std::string &str, const std::string &whitespace) {
  const auto str_begin = str.find_first_not_of(whitespace);
  if (str_begin == std::string::npos) {
    return "";  // no content
  }

  const auto str_end = str.find_last_not_of(whitespace);
  const auto str_range = str_end - str_begin + 1;
  return str.substr(str_begin, str_range);
}

// std::string &ltrim(std::string &s) {
//   s.erase(s.begin(), std::find_if(s.begin(), s.end(),
//         std::not1(std::ptr_fun<int, int>(std::isspace))));
//   return s;
// }
//
// std::string &rtrim(std::string &s) {
//   s.erase(std::find_if(s.rbegin(), s.rend(),
//         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
//   return s;
// }
//
// std::string &trim(std::string &s) {
//   return ltrim(rtrim(s));
// }

void strip(std::string &str, char delim) {
  str.erase(std::remove(str.begin(), str.end(), delim), str.end());
}

void split(const std::string s, char delim, std::vector<std::string> &out) {
  std::string element;
  std::istringstream iss(s);

  while (std::getline(iss, element, delim)) {
    strip(element, '\n');
    element = strim(element);
    out.push_back(element);
  }
}

}  // namespace yarl
