#include "yarl/optimization/optimizers/lls.hpp"

namespace yarl {

int lls_solve(MatX A, MatX b, VecX &x) {
  x = (A.transpose() * A).inverse() * A.transpose() * b;

  return 0;
}

}  // end of yarl namespace
