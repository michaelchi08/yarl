#ifndef ESTIMATION_PF_HPP
#define ESTIMATION_PF_HPP

#include <functional>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

class ParticleFilter {
public:
  bool initialized;
  VecX mu;

  int M;

  // VecX mu_p;
  // MatX S_p;

  ParticleFilter(void);
  int init(int M, VecX mu);
  int estimate(std::vector<VecX> X_p, std::vector<VecX> hX_p, VecX y);
};

}  // end of yarl namespace
#endif
