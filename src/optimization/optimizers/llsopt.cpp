#include "yarl/optimization/optimizers/llsopt.hpp"

namespace yarl {

int llsopt_solve(const MatX &A, const MatX &b, VecX &x) {
  x = (A.transpose() * A).inverse() * A.transpose() * b;
  return 0;
}

}  // end of yarl namespace
