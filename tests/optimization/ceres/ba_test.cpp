#include "yarl/test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/optimization/ceres/ba.hpp"

#define TEST_DATA_1 "tests/data/optimization/ceres/ba/pts1.dat"
#define TEST_DATA_2 "tests/data/optimization/ceres/ba/pts2.dat"
#define TEST_DATA_3 "tests/data/optimization/ceres/ba/pts3d.dat"

namespace yarl {

TEST(BAResidual, constructor) {
  Mat3 K;
  Vec2 x;

  // setup
  K << 1.0, 0.0, 3.0, 0.0, 2.0, 4.0, 0.0, 0.0, 1.0;
  x << 130, 62;

  // test
  ceres::BAResidual r(K, x, true);
  EXPECT_FLOAT_EQ(K(0, 0), r.fx);
  EXPECT_FLOAT_EQ(K(1, 1), r.fy);
  EXPECT_FLOAT_EQ(K(0, 2), r.cx);
  EXPECT_FLOAT_EQ(K(1, 2), r.cy);
  EXPECT_FLOAT_EQ(x(0), r.x);
  EXPECT_FLOAT_EQ(x(1), r.y);
  EXPECT_FLOAT_EQ(true, r.origin);
}

TEST(BAResidual, test) {
  Mat3 K;
  Vec2 p;
  ceres::BAResidual r;

  double q[4];
  double c[3];
  double x[3];
  double e[2];

  // setup
  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
  p << 10, 10;

  q[0] = 0.0;
  q[1] = 0.0;
  q[2] = 0.0;
  q[3] = 0.0;

  c[0] = 0.0;
  c[1] = 0.0;
  c[2] = 0.0;

  x[0] = 10.0;
  x[1] = 10.0;
  x[2] = 1.0;

  r = ceres::BAResidual(K, p, false);
  r(q, c, x, e);
  std::cout << e[0] << std::endl;
  std::cout << e[1] << std::endl;
}

TEST(BundleAdjustment, constructor) {
  ceres::BundleAdjustment ba;
  EXPECT_FALSE(ba.configured);
}

TEST(BundleAdjustment, configure) {
  Mat3 K;
  MatX x1_pts, x2_pts;
  ceres::BundleAdjustment ba;

  // setup
  csv2mat(TEST_DATA_1, false, x1_pts);
  csv2mat(TEST_DATA_2, false, x2_pts);

  // test
  // K << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
  ba.configure(K, x1_pts, x2_pts);

  EXPECT_TRUE(ba.configured);
  EXPECT_EQ(x1_pts, ba.x1_pts);
  EXPECT_EQ(x2_pts, ba.x2_pts);
  // EXPECT_FLOAT_EQ(K(0, 0), ba.K(0, 0));
  // EXPECT_FLOAT_EQ(K(1, 1), ba.K(1, 1));
  // EXPECT_FLOAT_EQ(K(2, 2), ba.K(2, 2));
}

TEST(BundleAdjustment, solve) {
  Mat3 K;
  MatX x1_pts, x2_pts, pts3d;
  ceres::BundleAdjustment ba;
  struct timespec t;

  // setup
  csv2mat(TEST_DATA_1, false, x1_pts);
  csv2mat(TEST_DATA_2, false, x2_pts);
  csv2mat(TEST_DATA_3, false, pts3d);

  K << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;

  tic(&t);
  ba.configure(K, x1_pts, x2_pts);
  std::cout << mtoc(&t) << " ms" << std::endl << std::endl;

  // test
  tic(&t);
  ba.solve(pts3d);
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
}

}  // namespace yarl
