#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/graph.hpp"


namespace yarl {

TEST(FactorGraph, addVariable) {
  FactorGraph graph;
  auto var1 = new Pose3dVar(1);
  auto var2 = new Pose3dVar(2);
  auto var3 = new Pose3dVar(2);

  int retval1 = graph.addVariable(var1);
  int retval2 = graph.addVariable(var2);
  int retval3 = graph.addVariable(var3);

  EXPECT_EQ(0, retval1);
  EXPECT_EQ(0, retval2);
  EXPECT_EQ(-1, retval3);
  EXPECT_EQ(0u, graph.factors.size());
  EXPECT_EQ(2u, graph.variables.size());
}

TEST(FactorGraph, addFactor) {
  FactorGraph graph;
  MatX m;
  auto var1 = new Pose3dVar(1);
  auto var2 = new Point3dVar(2);
  auto vo_factor = new MonoVOFactor{var1, var2, m};

  int retval = graph.addFactor(vo_factor);

  EXPECT_EQ(0, retval);
  EXPECT_EQ(1u, graph.factors.size());
  EXPECT_EQ(2u, graph.variables.size());
}

}  // namespace yarl
