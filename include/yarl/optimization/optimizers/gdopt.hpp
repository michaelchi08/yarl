#ifndef YARL_OPTIMIZATION_OPTIMIZERS_GD_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_GD_HPP

#include <cmath>

#include "yarl/utils/utils.hpp"

namespace yarl {

#define EGDC "GDOpt is not configured!"
#define EGDF "Failed to execute GDOpt.f() [%s]"

/**
 * Gradient Desent Optimization
 */
class GDOpt {
public:
  bool configured;

  int max_iter;
  VecX eta;
  VecX x;
  std::function<double(VecX x)> f;

  GDOpt() : configured(false), max_iter(1000), eta(), x(), f(nullptr) {}

  int configure(int max_iter,
                const VecX &eta,
                const VecX &x,
                std::function<double(VecX x)> f);
  int calcGradient(VecX &df);
  int optimize();
};

}  // namespace yarl
#endif
