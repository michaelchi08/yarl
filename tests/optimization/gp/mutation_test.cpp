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

TEST(Mutation, constructor) {
  Mutation mutation;

  ASSERT_FLOAT_EQ(0.0, mutation.probability);

  ASSERT_EQ(UINITI, mutation.subtree_build_method);
  ASSERT_EQ(UINITI, mutation.subtree_max_depth);
}

TEST(Mutation, configure) {
  Mutation mutation;

  mutation.configure(1.0);
  ASSERT_FLOAT_EQ(1.0, mutation.probability);

  // ASSERT_EQ(UINITI, mutation.subtree_build_method);
  // ASSERT_EQ(UINITI, mutation.subtree_max_depth);
}

TEST(Mutation, pointMutation) {
  Mutation mutation;
  Tree tree;
  TreeConfig config;
  std::string s1, s2;

  // setup
  mutation.configure(1.0);
  config.configure(GROW_METHOD, 2);
  setupAddTree(tree, &config);

  // test and assert
  s1 = tree.toString();
  mutation.pointMutation(tree);
  s2 = tree.toString();

  std::cout << "tree: " << s1 << std::endl;
  std::cout << "mutated tree: " << s2 << std::endl;

  ASSERT_TRUE(s1.compare(s2) != 0);
}

TEST(Mutation, subtreeMutation) {
  Mutation mutation;
  Tree tree;
  TreeConfig config;
  std::string s1, s2;

  // setup
  mutation.configure(1.0);
  config.configure(GROW_METHOD, 2);
  setupAddTree(tree, &config);

  // test and assert
  s1 = tree.toString();
  mutation.subtreeMutation(tree);
  s2 = tree.toString();

  std::cout << "tree: " << s1 << std::endl;
  std::cout << "mutated tree: " << s2 << std::endl;

  ASSERT_TRUE(s1.compare(s2) != 0);
}

}  // end of gp namespace
}  // end of yarl namespace
