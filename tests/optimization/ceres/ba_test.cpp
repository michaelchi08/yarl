#include "yarl/test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/optimization/ceres/ba.hpp"

namespace yarl {

const auto TEST_DATA_1 = "tests/data/optimization/ceres/ba/pts1.dat";
const auto TEST_DATA_2 = "tests/data/optimization/ceres/ba/pts2.dat";
const auto TEST_DATA_3 = "tests/data/optimization/ceres/ba/pts3d.dat";

TEST(BAResidual, constructor) {
  Mat3 K;
  K << 1.0, 0.0, 3.0, 0.0, 2.0, 4.0, 0.0, 0.0, 1.0;
  Vec2 x = Vec2{130, 62};

  BAResidual residual(K, x, true);
  EXPECT_FLOAT_EQ(K(0, 0), residual.fx);
  EXPECT_FLOAT_EQ(K(1, 1), residual.fy);
  EXPECT_FLOAT_EQ(K(0, 2), residual.cx);
  EXPECT_FLOAT_EQ(K(1, 2), residual.cy);
  EXPECT_FLOAT_EQ(x(0), residual.x);
  EXPECT_FLOAT_EQ(x(1), residual.y);
  EXPECT_FLOAT_EQ(true, residual.origin);
}

TEST(BAResidual, test) {
  Mat3 K = Mat3::Identity();
  Vec2 p = Vec2{10, 10};

  double q[4] = {0.0, 0.0, 0.0, 0.0};
  double c[3] = {0.0, 0.0, 0.0};
  double x[3] = {10.0, 10.0, 1.0};
  double e[2] = {0.0, 0.0};

  BAResidual residual;
  residual = BAResidual(K, p, false);
  bool retval = residual(q, c, x, e);

  std::cout << e[0] << std::endl;
  std::cout << e[1] << std::endl;

  EXPECT_TRUE(retval);
  EXPECT_FLOAT_EQ(0.0, e[0]);
  EXPECT_FLOAT_EQ(0.0, e[1]);
}

TEST(BundleAdjustment, constructor) {
  BundleAdjustment ba;
  EXPECT_FALSE(ba.configured);
}

TEST(BundleAdjustment, configure) {
  // setup
  MatX x1_pts, x2_pts;
  csv2mat(TEST_DATA_1, false, x1_pts);
  csv2mat(TEST_DATA_2, false, x2_pts);

  // test
  Mat3 K = Mat3::Identity();
  BundleAdjustment ba;
  ba.configure(K, x1_pts, x2_pts);

  EXPECT_TRUE(ba.configured);
  EXPECT_EQ(x1_pts, ba.x1_pts);
  EXPECT_EQ(x2_pts, ba.x2_pts);
  EXPECT_TRUE(ba.K.isApprox(K));
}

TEST(BundleAdjustment, solve) {
  // setup
  MatX x1_pts, x2_pts, pts3d;
  csv2mat(TEST_DATA_1, false, x1_pts);
  csv2mat(TEST_DATA_2, false, x2_pts);
  csv2mat(TEST_DATA_3, false, pts3d);

  BundleAdjustment ba;
  Mat3 K = Mat3::Identity();
  ba.configure(K, x1_pts, x2_pts);

  // test
  struct timespec t;

  tic(&t);
  ba.solve();
  std::cout << mtoc(&t) << " ms" << std::endl << std::endl;

  std::cout << "q: (";
  std::cout << ba.q[1][0] << ", ";
  std::cout << ba.q[1][1] << ", ";
  std::cout << ba.q[1][2] << ", ";
  std::cout << ba.q[1][3] << ")";
  std::cout << std::endl;

  std::cout << "c: (";
  std::cout << ba.c[1][0] << ", ";
  std::cout << ba.c[1][1] << ", ";
  std::cout << ba.c[1][2] << ")";
  std::cout << std::endl;

  std::cout << "x: (";
  std::cout << ba.x[1][0] << ", ";
  std::cout << ba.x[1][1] << ", ";
  std::cout << ba.x[1][2] << ")";
  std::cout << std::endl;
}

}  // namespace yarl
