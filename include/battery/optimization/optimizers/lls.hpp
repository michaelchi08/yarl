#ifndef __OPTIMIZATION_OPTIMIZERS_LLS_HPP__
#define __OPTIMIZATION_OPTIMIZERS_LLS_HPP__

#include "battery/utils/utils.hpp"

namespace battery {

class LLSSolver {
public:
  bool configured;

  LLSSolver(void);
  int configure(void);
  int solve(MatX A, MatX b, VecX &x);
};

} // end of battery namespace
#endif
