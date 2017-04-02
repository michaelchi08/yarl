#ifndef YARL_ESTIMATION_KF_HPP
#define YARL_ESTIMATION_KF_HPP

#include <functional>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

class KF {
public:
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

  KF(void);
  int configure(VecX mu, MatX R, MatX C, MatX Q);
  int estimate(MatX A, VecX y);
};

}  // end of yarl namespace
#endif
