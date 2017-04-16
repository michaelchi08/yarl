#ifndef YARL_OPTIMIZATION_OPTIMIZERS_LMA_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_LMA_HPP

#include <cmath>
#include <float.h>

#include "yarl/utils/utils.hpp"

namespace yarl {

#define ELMAC "LMA is not configured!"
#define ELMAF "Failed to execute LMA.f() [%s]"
#define ELMAH "Hessian is not positive definite!"

#define LMA_BIND(X) std::bind(X, std::placeholders::_1, std::placeholders::_2)

class LMASettings {
public:
  int max_iter;
  double lambda;
  std::function<double(VecX x, VecX beta)> function;
  std::function<VecX(VecX x, VecX beta)> jacobian;
  int nb_inputs;
  int nb_params;

  MatX x;
  VecX y;
  VecX beta;

  LMASettings()
    : max_iter(100),
      lambda(0.01),
      function(nullptr),
      jacobian(nullptr),
      nb_inputs(0),
      nb_params(0),

      x(),
      y(),
      beta() {}
};

class LMAOpt {
public:
  bool configured;

  int max_iter;
  double lambda;
  std::function<double(VecX x, VecX beta)> function;
  std::function<VecX(VecX x, VecX beta)> jacobian;
  int nb_inputs;
  int nb_params;

  MatX x;
  VecX y;
  VecX beta;

  VecX y_est;
  VecX diff;

  MatX J;
  MatX H;

  double error;

  LMAOpt()
    : configured(false),

      max_iter(100),
      lambda(0.01),
      function(nullptr),
      jacobian(nullptr),
      nb_inputs(0),
      nb_params(0),

      x(),
      y(),
      beta(),

      y_est(),
      diff(),

      J(),
      H(),

      error(FLT_MAX) {}

  int configure(const LMASettings &settings);
  int evalFunction(const VecX &beta, double &error);
  int calcGradients(const VecX &beta);
  int iterate();
  int optimize();
};

}  // end of yarl namespace
#endif
