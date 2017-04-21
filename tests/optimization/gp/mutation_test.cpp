#include "yarl/test.hpp"
#include "yarl/optimization/gp/mutation.hpp"


namespace yarl {
namespace gp {

static void setupAddTree(Tree &t, TreeConfig *tc) {
  Node *n1, *n2, *n3;

  // setup
  n1 = new Node();
  n2 = new Node();
  n3 = new Node();

  n1->setAsBinaryFunc(ADD);
  n2->setAsConstant(1.0);
  n3->setAsConstant(2.0);

  n1->children[0] = n2;
  n1->children[1] = n3;

  t.root = n1;
  t.tc = tc;
  t.update();
}

TEST(Mutation, point_mutation) {
  Tree tree;
  TreeConfig config;
  std::string s1, s2;

  // setup
  config.configure(GROW_METHOD, 2);
  setupAddTree(tree, &config);

  // test
  s1 = tree.toString();
  point_mutation(1.0, tree);
  s2 = tree.toString();

  std::cout << "tree: " << s1 << std::endl;
  std::cout << "mutated tree: " << s2 << std::endl;

  EXPECT_TRUE(s1.compare(s2) != 0);
}

TEST(Mutation, subtreeMutation) {
  Tree tree;
  TreeConfig config;
  std::string s1, s2;

  // setup
  config.configure(GROW_METHOD, 2);
  setupAddTree(tree, &config);

  // test
  s1 = tree.toString();
  subtree_mutation(1.0, GROW_METHOD, 2, tree);
  s2 = tree.toString();

  std::cout << "tree: " << s1 << std::endl;
  std::cout << "mutated tree: " << s2 << std::endl;

  EXPECT_TRUE(s1.compare(s2) != 0);
}

}  // end of gp namespace
}  // end of yarl namespace
