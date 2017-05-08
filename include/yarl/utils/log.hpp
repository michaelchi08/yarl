#ifndef YARL_UTILS_LOG_HPP
#define YARL_UTILS_LOG_HPP

#include <stdio.h>

#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/**
 * `log_error` and `log_info` both are simple `fprintf()` that can be use to
 * write message `M` to `stderr` and `stdout`. For example:
 *
 *     log_error("Failed to load configuration file [%s]",
 *                config_file.c_str());
 *     log_info("Parameter was not found! Loading defaults!");
 */
#define log_error(M, ...)            \
  fprintf(stderr,                    \
          "[ERROR] [%s:%d] " M "\n", \
          __FILENAME__,              \
          __LINE__,                  \
          ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stdout, "[INFO] " M "\n", ##__VA_ARGS__)

#endif
