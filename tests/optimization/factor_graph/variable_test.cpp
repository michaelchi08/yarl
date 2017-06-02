#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"


namespace yarl {

TEST(Variable, constructor) {
  // TEST NOTSET
  Variable var1(NOTSET, 1);
  std::cout << var1 << std::endl;
  EXPECT_EQ(NOTSET, var1.type);
  EXPECT_EQ(1u, var1.id);
  EXPECT_EQ(1u, var1.value.size());

  // TEST POSE3D
  Variable var2(POSE3D, 2);
  std::cout << var2 << std::endl;
  EXPECT_EQ(POSE3D, var2.type);
  EXPECT_EQ(2u, var2.id);
  EXPECT_EQ(6u, var2.value.size());

  // TEST POINT3D
  Variable var3(POINT3D, 3);
  std::cout << var3 << std::endl;
  EXPECT_EQ(POINT3D, var3.type);
  EXPECT_EQ(3u, var3.id);
  EXPECT_EQ(3u, var3.value.size());
}

TEST(Pose3dVar, constructor) {
  Pose3dVar var(1);

  std::cout << var << std::endl;
  EXPECT_EQ(POSE3D, var.type);
  EXPECT_EQ(1u, var.id);
  EXPECT_EQ(6u, var.value.size());
}

TEST(Point3dVar, constructor) {
  Point3dVar var(1);

  std::cout << var << std::endl;
  EXPECT_EQ(POINT3D, var.type);
  EXPECT_EQ(1u, var.id);
  EXPECT_EQ(3u, var.value.size());
}

}  // namespace yarl
