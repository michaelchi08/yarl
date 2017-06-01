#ifndef YARL_OPTIMIZATION_OPTIMIZERS_LLSOPT_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_LLSOPT_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

/**
 * Linear Least Squares
 */
int llsopt_solve(const MatX &A, const MatX &b, VecX &x);

}  // namespace yarl
#endif
