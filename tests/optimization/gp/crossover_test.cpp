#include "yarl/test.hpp"
#include "yarl/optimization/gp/crossover.hpp"
#include "yarl/optimization/gp/tree.hpp"


namespace yarl {
namespace gp {

void setupAddTree(Tree &t) {
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
  t.update();
}

void setupSubTree(Tree &t) {
  Node *n1, *n2, *n3;

  // setup
  n1 = new Node();
  n2 = new Node();
  n3 = new Node();

  n1->setAsBinaryFunc(SUB);
  n2->setAsConstant(3.0);
  n3->setAsConstant(4.0);

  n1->children[0] = n2;
  n1->children[1] = n3;

  t.root = n1;
  t.update();
}

TEST(Crossover, constructor) {
  Crossover crossover;

  ASSERT_FLOAT_EQ(0.0, crossover.probability);
}

TEST(Crossover, pointCrossover) {
  Crossover crossover;
  Tree t1, t2;
  std::string s1, s2, s3, s4;

  // setup
  crossover.probability = 1.0;
  setupAddTree(t1);
  setupSubTree(t2);

  // test and assert
  s1 = t1.toString();
  s2 = t2.toString();

  std::cout << "t1: " << s1 << std::endl;
  std::cout << "t2: " << s2 << std::endl;

  crossover.pointCrossover(t1, t2);

  s3 = t1.toString();
  s4 = t2.toString();

  std::cout << "crossed t1: " << s3 << std::endl;
  std::cout << "crossed t2: " << s4 << std::endl;
  std::cout << std::endl;

  ASSERT_FLOAT_EQ(1.0, crossover.probability);
  ASSERT_TRUE(s1.compare(s3) != 0);
  ASSERT_TRUE(s1.compare(s4) != 0);
  ASSERT_TRUE(s2.compare(s3) != 0);
  ASSERT_TRUE(s2.compare(s4) != 0);
}

}  // end of gp namespace
}  // end of yarl namespace
