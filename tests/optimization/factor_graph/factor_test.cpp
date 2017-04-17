#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/factor.hpp"


namespace yarl {

TEST(Factor, constructor) {
  // TEST UNARY FACTOR
  Variable var(VariableType::POSE, 1);
  Factor f1(std::make_shared<Variable>(var), 100);
  f1.print();

  EXPECT_EQ(1u, f1.variables[0]->id);
  EXPECT_DOUBLE_EQ(100.0, *static_cast<double *>(f1.measurement));

  // TEST BINARY FACTOR
  auto var1 = std::make_shared<Variable>(VariableType::POSE, 1);
  auto var2 = std::make_shared<Variable>(VariableType::POSE, 2);
  Factor f2(var1, var2, 100);
  f2.print();

  EXPECT_EQ(1u, f2.variables[0]->id);
  EXPECT_EQ(2u, f2.variables[1]->id);
  EXPECT_DOUBLE_EQ(100.0, *static_cast<double *>(f2.measurement));
}

}  // end of yarl namespace
