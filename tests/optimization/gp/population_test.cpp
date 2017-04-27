#include "yarl/test.hpp"
#include "yarl/optimization/gp/population.hpp"

#define TEST_DATA "./tests/data/optimization/gp/sine.csv"

namespace yarl {
namespace gp {

TEST(Population, constructor) {
  Population p;

  EXPECT_EQ(0u, p.individuals.size());
  EXPECT_EQ(NULL, p.tree_config);
}

TEST(Population, configure) {
  Population p;
  TreeConfig tree_config;

  tree_config.configure(GROW_METHOD, 2);
  p.configure(10, &tree_config);
  EXPECT_EQ(10u, p.individuals.size());
  EXPECT_TRUE(&tree_config == p.tree_config);
}

TEST(Population, evaluate) {
  Population p;
  Data d;
  TreeConfig tree_config;

  tree_config.configure(GROW_METHOD, 2);
  d.load(TEST_DATA);
  p.configure(10, &tree_config);
  p.evaluate(d, "x");
}

TEST(Population, clear) {
  Population p;
  TreeConfig tree_config;

  p.configure(10, &tree_config);
  p.clear();

  EXPECT_EQ(0u, p.individuals.size());
  EXPECT_TRUE(&tree_config == p.tree_config);
}

TEST(Population, best) {
  Population p;
  TreeConfig tree_config;
  Tree tree;

  tree_config.configure(GROW_METHOD, 2);
  p.configure(10, &tree_config);
  p.individuals[0]->score = 0.0;
  p.individuals[1]->score = 0.0;
  p.individuals[2]->score = 0.0;
  p.individuals[3]->score = 0.0;
  p.individuals[4]->score = 0.0;
  p.individuals[5]->score = 1.0;
  p.individuals[6]->score = 2.0;
  p.individuals[7]->score = 3.0;
  p.individuals[8]->score = 0.0;
  p.individuals[9]->score = 0.0;
  p.best(tree);

  EXPECT_FLOAT_EQ(3.0, tree.score);
}

TEST(Population, copyFrom) {
  Population p1, p2;
  TreeConfig tree_config;
  Tree tree;
  std::string s1, s2;

  // setup
  tree_config.configure(GROW_METHOD, 2);
  p1.configure(5, &tree_config);

  // test
  p2.copyFrom(p1);
  s1 = p1.individuals[0]->toString();
  s2 = p2.individuals[0]->toString();

  // print
  std::cout << "Population 1: " << std::endl;
  p1.print();
  std::cout << std::endl;

  std::cout << "Population 2: " << std::endl;
  p2.print();

  // EXPECT
  EXPECT_EQ(p2.individuals.size(), p1.individuals.size());
  EXPECT_EQ(s1, s2);
}

}  // end of gp namespace
}  // end of yarl namespace
