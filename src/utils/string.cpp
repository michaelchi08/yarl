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

void strip(std::string &str, char delim) {
  str.erase(std::remove(str.begin(), str.end(), delim), str.end());
}

void split(const std::string s, char delim, std::vector<std::string> &out) {
  std::string element;
  std::istringstream iss(s);

  while (std::getline(iss, element, delim)) {
    strip(element, '\n');
    out.push_back(strim(element));
  }
}

}  // end of yarl namespace
