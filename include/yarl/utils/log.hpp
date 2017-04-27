#ifndef YARL_UTILS_LOG_HPP
#define YARL_UTILS_LOG_HPP

#include <stdio.h>

#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define log_error(M, ...)            \
  fprintf(stderr,                    \
          "[ERROR] [%s:%d] " M "\n", \
          __FILENAME__,              \
          __LINE__,                  \
          ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stdout, "[INFO] " M "\n", ##__VA_ARGS__)

#endif
