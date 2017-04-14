#ifndef YARL_OPTIMIZATION_OPTIMIZERS_LLSOPT_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_LLSOPT_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

int llsopt_solve(const MatX &A, const MatX &b, VecX &x);

}  // end of yarl namespace
#endif
