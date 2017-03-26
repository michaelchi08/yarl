#ifndef OPTIMIZATION_OPTIMIZERS_LMA_HPP
#define OPTIMIZATION_OPTIMIZERS_LMA_HPP

#include <cmath>
#include <float.h>

#include "yarl/utils/utils.hpp"

namespace yarl {

#define ELMAC "LMA is not configured!"
#define ELMAF "Failed to execute LMA.f() [%s]"
#define ELMAH "Hessian is not positive definite!"

#define LMA_BIND(X) std::bind(X, std::placeholders::_1, std::placeholders::_2)

struct lmaopt_settings {
  int max_iter;
  double lambda;
  std::function<double(VecX x, VecX beta)> function;
  std::function<VecX(VecX x, VecX beta)> jacobian;
  int nb_inputs;
  int nb_params;

  MatX x;
  VecX y;
  VecX beta;
};

struct lmaopt {
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
};

void lmaopt_default_settings(struct lmaopt_settings *settings);
void lmaopt_setup(struct lmaopt *opt);
int lmaopt_configure(struct lmaopt *opt, struct lmaopt_settings *settings);
int lmaopt_evaluate_function(struct lmaopt *opt, VecX beta, double *error);
int lmaopt_calculate_gradient(struct lmaopt *opt, VecX beta);
int lmaopt_iterate(struct lmaopt *opt);
int lmaopt_optimize(struct lmaopt *opt);

}  // end of yarl namespace
#endif
