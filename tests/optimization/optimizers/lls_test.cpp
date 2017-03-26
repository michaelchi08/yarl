#include <gtest/gtest.h>

#include "yarl/optimization/optimizers/lls.hpp"
#include "yarl/utils/math.hpp"

namespace yarl {

TEST(LLSSolver, constructor) {
  LLSSolver solver;

  ASSERT_EQ(solver.configured, false);
}

TEST(LLSSolver, configure) {
  LLSSolver solver;

  solver.configure();
  ASSERT_EQ(solver.configured, true);
}

TEST(LLSSolver, solve) {
  LLSSolver solver;
  MatX A(4, 2);
  VecX b(4);
  VecX x;

  A << 1, 1, 1, 2, 1, 3, 1, 4;

  b << 6, 5, 7, 10;

  solver.configure();
  solver.solve(A, b, x);

  ASSERT_FLOAT_EQ(x(0), 3.5);
  ASSERT_FLOAT_EQ(x(1), 1.4);
}

}  // end of yarl namespace
