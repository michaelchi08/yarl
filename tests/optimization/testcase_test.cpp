#include "yarl/test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/optimization/testcase.hpp"

namespace yarl {

TEST(Testcase, constructor) {
  TestCase testcase;

  EXPECT_FALSE(testcase.configured);
}

TEST(Testcase, configure) {
  TestCase testcase;

  testcase.configure();
  EXPECT_TRUE(testcase.configured);
}

TEST(TestCase, createP) {
  TestCase testcase;
  Mat3 K, R;
  MatX P;
  Vec3 t;

  // setup
  // clang-format off
  K << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  R << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  t << 1.0, 2.0, 3.0;
  // clang-format on

  // test
  testcase.createP(K, R, t, P);
  // std::cout << P << std::endl;

  EXPECT_FLOAT_EQ(1.0, P(0, 0));
  EXPECT_FLOAT_EQ(1.0, P(1, 1));
  EXPECT_FLOAT_EQ(1.0, P(2, 2));

  EXPECT_FLOAT_EQ(-1.0, P(0, 3));
  EXPECT_FLOAT_EQ(-2.0, P(1, 3));
  EXPECT_FLOAT_EQ(-3.0, P(2, 3));
}

TEST(Testcase, generateRandom3DPoints) {
  TestCase testcase;
  TestRange range;
  MatX pts;

  range.x_min = 0.0;
  range.x_max = 1.0;

  range.y_min = 0.0;
  range.y_max = 1.0;

  range.z_min = 0.1;
  range.z_max = 1.0;

  testcase.configure();
  testcase.generateRandom3DPoints(range, 10, pts);

  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(pts(i, 0) > 0.0);
    EXPECT_TRUE(pts(i, 0) < 1.0);

    EXPECT_TRUE(pts(i, 1) > 0.0);
    EXPECT_TRUE(pts(i, 1) < 1.0);

    EXPECT_TRUE(pts(i, 2) > 0.0);
    EXPECT_TRUE(pts(i, 2) < 1.0);
  }
}

TEST(TestCase, project3DTo2D) {
  TestRange range;
  TestCase testcase;
  MatX pts_3d;
  MatX pts_2d;
  Mat3 K, R;
  Vec3 t;

  // setup
  range.x_min = -1.0;
  range.x_max = 1.0;

  range.y_min = -1.0;
  range.y_max = 1.0;

  range.z_min = 2.0;
  range.z_max = 5.0;

  // setup
  // clang-format off
  K << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  R << 1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,
       0.0, 0.0, 1.0;
  t << 0.0, 0.0, 0.0;
  // clang-format on

  testcase.generateRandom3DPoints(range, 10, pts_3d);
  testcase.project3DTo2D(K, R, t, pts_3d, pts_2d);
}

TEST(TestCase, generateTestCase) {
  TestRange range;
  TestCase testcase;
  MatX pts1, pts2, pts3d;

  // setup
  range.x_min = -1.0;
  range.x_max = 1.0;

  range.y_min = -1.0;
  range.y_max = 1.0;

  range.z_min = 2.0;
  range.z_max = 5.0;

  testcase.generateTestCase(range, pts1, pts2, pts3d);

  mat2csv("/tmp/pts1.dat", pts1);
  mat2csv("/tmp/pts2.dat", pts2);
  mat2csv("/tmp/pts3d.dat", pts3d);
}

}  // end of yarl namespace
