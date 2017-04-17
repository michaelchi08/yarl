#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"


namespace yarl {

TEST(Variable, constructor) {
  Variable var1(VariableType::POSE, 1);
  EXPECT_EQ(VariableType::POSE, var1.type);
  EXPECT_EQ(1u, var1.id);

  Variable var2(VariableType::LANDMARK, 2);
  EXPECT_EQ(VariableType::LANDMARK, var2.type);
  EXPECT_EQ(2u, var2.id);
}

}  // end of yarl namespace
