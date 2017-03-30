#ifndef YARL_UTILS_STRING_HPP
#define YARL_UTILS_STRING_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace yarl {

std::string strim(const std::string &str,
                  const std::string &whitespace = " \t");
void strip(std::string &str, char delim);
void split(const std::string s, char delim, std::vector<std::string> &out);

}  // end of yarl namespace
#endif
