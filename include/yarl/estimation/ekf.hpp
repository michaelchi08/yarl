#ifndef ESTIMATION_EKF_HPP
#define ESTIMATION_EKF_HPP

#include <functional>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

struct ekf {
  VecX mu;

  MatX R;
  MatX Q;

  MatX S;
  MatX I;
  MatX K;

  VecX mu_p;
  MatX S_p;
};

int ekf_setup(struct ekf *e, VecX mu, MatX R, MatX Q);
int ekf_prediction_update(struct ekf *e, VecX g, MatX G);
int ekf_measurement_update(struct ekf *e, VecX h, MatX H, VecX y);

}  // end of yarl namespace
#endif
