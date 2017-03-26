#ifndef OPTIMIZATION_OPTIMIZERS_LLS_HPP
#define OPTIMIZATION_OPTIMIZERS_LLS_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

int lls_solve(MatX A, MatX b, VecX &x);

}  // end of yarl namespace
#endif
