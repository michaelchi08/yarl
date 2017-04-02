#ifndef YARL_ESTIMATION_EKF_HPP
#define YARL_ESTIMATION_EKF_HPP

#include <functional>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

struct EKF {
  VecX mu;

  MatX R;
  MatX Q;

  MatX S;
  MatX I;
  MatX K;

  VecX mu_p;
  MatX S_p;

  EKF(void);
  int configure(VecX mu, MatX R, MatX Q);
  int predictionUpdate(VecX g, MatX G);
  int measurementUpdate(VecX h, MatX H, VecX y);
};

}  // end of yarl namespace
#endif
