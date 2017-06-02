#ifndef YARL_UTILS_UTILS_HPP
#define YARL_UTILS_UTILS_HPP

#include "yarl/utils/config.hpp"
#include "yarl/utils/data.hpp"
#include "yarl/utils/file.hpp"
#include "yarl/utils/log.hpp"
#include "yarl/utils/math.hpp"
#include "yarl/utils/opencv.hpp"
#include "yarl/utils/stats.hpp"
#include "yarl/utils/string.hpp"
#include "yarl/utils/time.hpp"

// ERROR MESSAGES
#define MKDIR_PERMISSION "Permission denied! Failed to mkdir [%s]!"
#define MKDIR_INVALID "[%s] is not a dir!"
#define MKDIR_EXISTS "[%s] already exists!"
#define MKDIR_FAILED "Failed to create [%s]!"

// MACROS
#define UNUSED(expr) \
  do {               \
    (void) (expr);   \
  } while (0)


#define check(A, E) \
  if (!(A)) {       \
    goto E;         \
  }

#endif
