#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/factor_graph.hpp"


namespace yarl {

TEST(FactorGraph, addUnaryFactor) {
  FactorGraph graph;
  graph.addUnaryFactor<double>(VariableType::POSE, 1, 2.0);

  ASSERT_EQ(1u, graph.graph.size());
  ASSERT_EQ(1u, graph.factors.size());
}

TEST(FactorGraph, addBinaryFactor) {
  FactorGraph graph;

  graph.addBinaryFactor<double>(
    VariableType::POSE, 1, VariableType::POSE, 2, 2);
  ASSERT_EQ(2, (int) graph.graph.size());
  ASSERT_EQ(1, (int) graph.factors.size());
}

TEST(FactorGraph, print) {
  FactorGraph graph;

  graph.addUnaryFactor(VariableType::POSE, 1, 2);
  graph.addBinaryFactor(VariableType::POSE, 1, VariableType::POSE, 2, 2);
  graph.addBinaryFactor(VariableType::POSE, 2, VariableType::POSE, 3, 2);

  Vec2 measurement;
  measurement << 100.0, 200.0;
  graph.addBinaryFactor(
    VariableType::POSE, 1, VariableType::POSE, 1, measurement);
  graph.addBinaryFactor(
    VariableType::POSE, 2, VariableType::POSE, 2, measurement);

  graph.print();
}

}  // end of yarl namespace
