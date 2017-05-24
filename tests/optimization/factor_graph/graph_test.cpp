#include "yarl/test.hpp"
#include "yarl/optimization/factor_graph/graph.hpp"


namespace yarl {

// TEST(FactorGraph, addUnaryFactor) {
//   FactorGraph graph;
//   graph.addUnaryFactor<PoseVar, double>(1, 2.0);
//   graph.addUnaryFactor<PoseVar, int>(1, 1);
//
//   EXPECT_EQ(2u, graph.graph.size());
//   EXPECT_EQ(2u, graph.factors.size());
// }

// TEST(FactorGraph, addBinaryFactor) {
//   FactorGraph graph;
//
//   graph.addBinaryFactor<PoseVar, PoseVar, double>(1, 2, 2);
//   EXPECT_EQ(2u, graph.graph.size());
//   EXPECT_EQ(1u, graph.factors.size());
// }
//
// TEST(FactorGraph, print) {
//   FactorGraph graph;
//
//   graph.addUnaryFactor<PoseVar, int>(1, 1);
//   graph.addBinaryFactor<PoseVar, PoseVar, int>(2, 3, 2);
//   graph.addBinaryFactor<PoseVar, PoseVar, int>(3, 4, 3);
//
//   Vec2 z;
//   z << 100.0, 200.0;
//   graph.addBinaryFactor<PoseVar, PoseVar, Vec2>(1, 2, z);
//   graph.addBinaryFactor<PoseVar, PoseVar, Vec2>(2, 3, z);
//
//   graph.print();
// }

}  // end of yarl namespace
