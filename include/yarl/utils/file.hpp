#ifndef YARL_UTILS_FILESYSTEM_HPP
#define YARL_UTILS_FILESYSTEM_HPP

#include <stdio.h>
#include <dirent.h>

#include <iostream>
#include <numeric>
#include <cerrno>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

#include "yarl/utils/log.hpp"

namespace yarl {

/// Extract file name from `path`
std::string basefile(const std::string &path);

/// Extract dir name from `path`
std::string basedir(const std::string &path);

/// Remove directory at `path`
int remove_dir(const std::string &path);

/// Remove trailing slash
void rmtrailslash(std::string &path);
std::string rmtrailslash(const std::string &path);

/// Check to see if `file_path` exists, returns boolean.
bool file_exists(const std::string &file_path);

/**
 * Splits `path` with the `/` token, returns separated path elements in the
 * form of `std::vector<std::string>`.
 */
std::vector<std::string> path_split(const std::string &path);

/**
 * Combine `path1` with `path2`, the result is written to `out`. This
 * function is modeled after python's `os.path.join` function. Example usage:
 *
 *     paths_combine("/a/b", "c/d", out) --> out = "/a/b/c/d"
 *     paths_combine("/a/b", "../", out) --> out = "/a"
 *     paths_combine("/a/b/c", "../..", out) --> out = "/a"
 */
void paths_combine(const std::string &path1,
                   const std::string &path2,
                   std::string &out);

}  // end of yarl namepsace
#endif
