#ifndef OPTIMIZATION_OPTIMIZERS_LLS_HPP
#define OPTIMIZATION_OPTIMIZERS_LLS_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

class LLSSolver {
public:
  bool configured;

  LLSSolver(void);
  int configure(void);
  int solve(MatX A, MatX b, VecX &x);
};

}  // end of yarl namespace
#endif
