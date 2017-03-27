#include <gtest/gtest.h>

#include "yarl/optimization/optimizers/llsopt.hpp"
#include "yarl/utils/math.hpp"

namespace yarl {

TEST(lls, solve) {
  MatX A(4, 2);
  VecX b(4);
  VecX x;

  // clang-format off
  A << 1, 1, 1, 2,
       1, 3, 1, 4;
  b << 6, 5, 7, 10;
  // clang-format on

  llsopt_solve(A, b, x);
  ASSERT_FLOAT_EQ(x(0), 3.5);
  ASSERT_FLOAT_EQ(x(1), 1.4);
}

}  // end of yarl namespace
