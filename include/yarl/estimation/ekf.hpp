#ifndef ESTIMATION_EKF_HPP
#define ESTIMATION_EKF_HPP

#include <functional>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

class ExtendedKalmanFilter {
public:
  bool initialized;
  VecX mu;

  MatX R;
  MatX Q;

  MatX S;
  MatX I;
  MatX K;

  VecX mu_p;
  MatX S_p;

  ExtendedKalmanFilter(void);
  int init(VecX mu, MatX R, MatX Q);
  int predictionUpdate(VecX g, MatX G);
  int measurementUpdate(VecX h, MatX H, VecX y);
};

}  // end of yarl namespace
#endif
