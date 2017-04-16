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

  EKF();
  int configure(const VecX &mu, const MatX &R, const MatX &Q);
  int predictionUpdate(const VecX &g, const MatX &G);
  int measurementUpdate(const VecX &h, const MatX &H, const VecX &y);
};

}  // end of yarl namespace
#endif
