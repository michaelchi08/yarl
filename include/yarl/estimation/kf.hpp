#ifndef ESTIMATION_KF_HPP
#define ESTIMATION_KF_HPP

#include <functional>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

struct kf {
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
};

int kf_setup(struct kf *e, VecX mu, MatX R, MatX C, MatX Q);
int kf_estimate(struct kf *e, MatX A, VecX y);

}  // end of yarl namespace
#endif
