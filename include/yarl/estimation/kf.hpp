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

  KF()
    : mu(),

      B(),
      R(),

      C(),
      Q(),

      S(),
      I(),
      K(),

      mu_p(),
      S_p() {}

  int configure(const VecX &mu, const MatX &R, const MatX &C, const MatX &Q);
  int estimate(const MatX &A, const VecX &y);
};

}  // end of yarl namespace
#endif
