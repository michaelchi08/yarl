#ifndef YARL_OPTIMIZATION_OPTIMIZERS_GDOPT_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_GDOPT_HPP

#include <cmath>

#include "yarl/utils/utils.hpp"

namespace yarl {

#define EGDC "GDOpt is not configured!"
#define EGDF "Failed to execute GDOpt.f() [%s]"

struct gdopt {
  bool configured;

  int max_iter;
  VecX eta;
  VecX x;
  std::function<double(VecX x)> f;
};

void gdopt_setup(struct gdopt *opt);
int gdopt_configure(struct gdopt *opt,
                    int max_iter,
                    VecX eta,
                    VecX x,
                    std::function<double(VecX x)> f);
int gdopt_calculate_gradient(struct gdopt *opt, VecX &df);
int gdopt_optimize(struct gdopt *opt);

}  // end of yarl namespace
#endif
