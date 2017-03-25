#ifndef ESTIMATION_KF_HPP
#define ESTIMATION_KF_HPP

#include <functional>
#include <iostream>

#include "battery/utils/utils.hpp"

namespace battery {

class KalmanFilter {
public:
  bool initialized;
  VecX mu;

  MatX B;
  MatX R;

  MatX C;
  MatX Q;

  MatX S;
  MatX I;
  MatX K;

  VecX mu_p;
  MatX S_p;

  KalmanFilter(void);
  int init(VecX mu, MatX R, MatX C, MatX Q);
  int estimate(MatX A, VecX y);
};

}  // end of battery namespace
#endif
