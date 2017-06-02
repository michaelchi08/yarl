#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/factor.hpp"


namespace yarl {

TEST(Factor, constructor) {
  // TEST DEFAULT CONSTRUCTOR
  Factor f1;
  MatX m = MatX::Zero(1, 1);

  EXPECT_FALSE(f1.valid);
  EXPECT_EQ(0, f1.type);
  EXPECT_EQ(0, f1.arity);
  EXPECT_EQ(0u, f1.variables.size());
  EXPECT_TRUE(f1.measurement.isApprox(m));

  // TEST UNARY CONSTRUCTOR
  Pose3dVar var1 = Pose3dVar(1);
  Factor f2{ODOM, &var1, m};

  EXPECT_FALSE(f2.valid);
  EXPECT_EQ(ODOM, f2.type);
  EXPECT_EQ(1, f2.arity);
  EXPECT_EQ((VarId) 1, f2.variables[0]->id);
  EXPECT_TRUE(f2.measurement.isApprox(m));

  // TEST BINARY CONSTRUCTOR
  Pose3dVar var2 = Pose3dVar(2);
  Factor f3{MONOVO, &var1, &var2, m};

  EXPECT_FALSE(f3.valid);
  EXPECT_EQ(MONOVO, f3.type);
  EXPECT_EQ(2, f3.arity);
  EXPECT_EQ((VarId) 1, f3.variables[0]->id);
  EXPECT_EQ((VarId) 2, f3.variables[1]->id);
  EXPECT_TRUE(f3.measurement.isApprox(m));
}

TEST(OdomFactor, constructor) {
  Pose3dVar pose1 = Pose3dVar(1);
  Pose3dVar pose2 = Pose3dVar(2);
  MatX m = MatX::Zero(1, 1);
  OdomFactor odom_factor{&pose1, &pose2, m};

  std::cout << odom_factor << std::endl;
  EXPECT_TRUE(odom_factor.valid);
  EXPECT_EQ(ODOM, odom_factor.type);
  EXPECT_EQ(2, odom_factor.arity);
  EXPECT_EQ((VarId) 1, odom_factor.variables[0]->id);
  EXPECT_EQ((VarId) 2, odom_factor.variables[1]->id);
  EXPECT_TRUE(odom_factor.measurement.isApprox(m));
}

TEST(MonoVOFactor, constructor) {
  Pose3dVar pose = Pose3dVar(1);
  Point3dVar point = Point3dVar(2);
  MatX m = MatX::Zero(1, 1);
  MonoVOFactor monovo_factor{&pose, &point, m};

  std::cout << monovo_factor << std::endl;
  EXPECT_TRUE(monovo_factor.valid);
  EXPECT_EQ(MONOVO, monovo_factor.type);
  EXPECT_EQ(2, monovo_factor.arity);
  EXPECT_EQ((VarId) 1, monovo_factor.variables[0]->id);
  EXPECT_EQ((VarId) 2, monovo_factor.variables[1]->id);
  EXPECT_TRUE(monovo_factor.measurement.isApprox(m));
}

}  // namespace yarl
