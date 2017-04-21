#ifndef YARL_UTILS_FILESYSTEM_HPP
#define YARL_UTILS_FILESYSTEM_HPP

#include <stdio.h>

#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>

namespace yarl {

std::string basefile(const std::string &path);
std::string basedir(const std::string &path);
void rmtrailslash(std::string &path);
std::string rmtrailslash(const std::string &path);
bool file_exists(const std::string &file_path);
std::vector<std::string> path_split(const std::string &path);
void paths_combine(const std::string &path1,
                   const std::string &path2,
                   std::string &out);

}  // end of yarl namepsace
#endif
