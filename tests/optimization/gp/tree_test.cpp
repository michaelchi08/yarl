#include "yarl/test.hpp"
#include "yarl/optimization/gp/tree.hpp"

#define TEST_SINE_DATA "./tests/data/optimization/gp/sine.csv"
#define TEST_SIMPLE_DATA "./tests/data/optimization/gp/simple.csv"
#define TEST_CIRCLE_DATA "./tests/data/optimization/gp/circle.csv"
#define TEST_ELLIPTIC_DATA "./tests/data/optimization/gp/elliptic.csv"
#define TEST_IMPLICIT_DATA "./tests/data/optimization/gp/implicit.csv"

namespace yarl {
namespace gp {

void setupSineTree(Tree &t) {
  Node *n1, *n2, *n3, *n4, *n5;

  // setup
  n1 = new Node();
  n2 = new Node();
  n3 = new Node();
  n4 = new Node();
  n5 = new Node();

  n1->setAsUnaryFunc(SIN);
  n2->setAsBinaryFunc(MUL);
  n3->setAsUnaryFunc(RAD);
  n4->setAsConstant(100.0);
  n5->setAsInput("x");

  n1->children[0] = n2;
  n2->children[0] = n3;
  n2->children[1] = n5;
  n3->children[0] = n4;

  t.root = n1;
}

TEST(TreeConfig, configure) {
  TreeConfig tc;

  tc.configure(FULL_METHOD, 2);
  ASSERT_EQ(5, (int) tc.unary_functions.size());
  ASSERT_EQ(5, (int) tc.binary_functions.size());
  ASSERT_EQ(11, (int) tc.constants.size());
  ASSERT_EQ(0, (int) tc.inputs.size());
}

TEST(TreeConfig, randomUnaryFunction) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomUnaryFunction(node);
    ASSERT_EQ(0, retval);
    ASSERT_EQ(UFUNC, node.type);
    ASSERT_EQ(1, node.arity);
  }
}

TEST(TreeConfig, randomBinaryFunction) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomBinaryFunction(node);
    ASSERT_EQ(0, retval);
    ASSERT_EQ(BFUNC, node.type);
    ASSERT_EQ(2, node.arity);
  }
}

TEST(TreeConfig, randomFunction) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomFunction(node);
    ASSERT_EQ(0, retval);
    ASSERT_TRUE(node.type == UFUNC || node.type == BFUNC);
    ASSERT_TRUE(node.arity == 1 || node.arity == 2);
  }
}

TEST(TreeConfig, randomInput) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  tc.inputs.push_back("x");
  tc.inputs.push_back("y");
  for (int i = 0; i < 10; i++) {
    retval = tc.randomInput(node);
    ASSERT_EQ(0, retval);
    ASSERT_EQ(INPUT, node.type);
  }
}

TEST(TreeConfig, randomConstant) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomConstant(node);
    ASSERT_EQ(0, retval);
    ASSERT_EQ(CONST, node.type);
  }
}

TEST(TreeConfig, randomTerminal) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomTerminal(node);
    ASSERT_EQ(0, retval);
    ASSERT_TRUE(node.type == INPUT || node.type == CONST);
  }
}

TEST(Tree, constructor) {
  Tree tree;

  ASSERT_EQ(0, (int) tree.chromosome.size());

  ASSERT_EQ(0, tree.nb_inputs);
  ASSERT_EQ(0, tree.nb_constants);
  ASSERT_EQ(0, tree.nb_functions);

  ASSERT_EQ(0, tree.size);
  ASSERT_EQ(0, tree.depth);

  ASSERT_EQ(0, tree.error);
  ASSERT_EQ(0, tree.score);
  ASSERT_EQ(0, tree.hits);
  ASSERT_EQ(0, tree.evaluated);
}

TEST(Tree, configure) {
  Tree tree;
  TreeConfig tc;
  Data data;

  data.load(TEST_SINE_DATA);
  tree.configure(&tc, data);
  ASSERT_EQ(0, (int) tree.chromosome.size());

  ASSERT_EQ(0, tree.nb_inputs);
  ASSERT_EQ(0, tree.nb_constants);
  ASSERT_EQ(0, tree.nb_functions);

  ASSERT_EQ(0, tree.size);
  ASSERT_EQ(0, tree.depth);

  ASSERT_EQ(0, tree.error);
  ASSERT_EQ(0, tree.score);
  ASSERT_EQ(0, tree.hits);
  ASSERT_EQ(0, tree.evaluated);

  ASSERT_TRUE(&tc == tree.tc);
}

TEST(Tree, clear) {
  Tree tree;
  TreeConfig tc;
  Data data;

  data.load(TEST_SINE_DATA);
  tree.configure(&tc, data);
  tree.clear();
  ASSERT_EQ(0, (int) tree.chromosome.size());

  ASSERT_EQ(0, tree.nb_inputs);
  ASSERT_EQ(0, tree.nb_constants);
  ASSERT_EQ(0, tree.nb_functions);

  ASSERT_EQ(0, tree.size);
  ASSERT_EQ(0, tree.depth);

  ASSERT_EQ(0, tree.error);
  ASSERT_EQ(0, tree.score);
  ASSERT_EQ(0, tree.hits);
  ASSERT_EQ(0, tree.evaluated);
}

TEST(Tree, copyFrom) {
  Tree t1, t2;
  std::string s;

  setupSineTree(t1);
  t2.copyFrom(t1);

  s = t2.root->toString();
  ASSERT_EQ("F[SIN]", s);

  s = t2.root->children[0]->children[0]->toString();
  ASSERT_EQ("F[RAD]", s);

  s = t2.root->children[0]->toString();
  ASSERT_EQ("F[MUL]", s);

  s = t2.root->children[0]->children[0]->children[0]->toString();
  ASSERT_EQ("T[100]", s);

  s = t2.root->children[0]->children[1]->toString();
  ASSERT_EQ("T[x]", s);
}

TEST(Tree, update) {
  Tree t;

  setupSineTree(t);
  t.update();

  ASSERT_EQ(5, (int) t.chromosome.size());
  ASSERT_EQ("T[100]", t.chromosome[0]->toString());
  ASSERT_EQ("F[RAD]", t.chromosome[1]->toString());
  ASSERT_EQ("T[x]", t.chromosome[2]->toString());
  ASSERT_EQ("F[MUL]", t.chromosome[3]->toString());
  ASSERT_EQ("F[SIN]", t.chromosome[4]->toString());
}

TEST(Tree, generate) {
  Tree t;
  TreeConfig tc;
  Data data;

  data.load(TEST_SINE_DATA);
  tc.configure(FULL_METHOD, 2);
  t.configure(&tc, data);
  t.generate();
  t.printStack();
}

TEST(Tree, prepData) {
  Tree t;
  TreeConfig tc;
  Data data;
  Node node;

  // setup
  tc.configure(FULL_METHOD, 2);
  data.load(TEST_SINE_DATA);
  t.configure(&tc, data);

  // prep input data
  node.setAsInput("x");
  node.nth_child = 0;
  t.prepData(data, node);
  ASSERT_FLOAT_EQ(0.0, t.f_in(0, 0));
  ASSERT_FLOAT_EQ(10.0, t.f_in(10, 0));

  // prep const data
  node.setAsConstant(23.0);
  node.nth_child = 0;
  t.prepData(data, node);
  ASSERT_FLOAT_EQ(23.0, t.f_in(10, 0));

  // prep feval data
  node.type = FEVAL;
  node.nth_child = 0;
  node.data = VecX(data.rows);
  for (int i = 0; i < data.rows; i++) {
    node.data(i) = 23.0;
  }
  t.prepData(data, node);
  ASSERT_FLOAT_EQ(23.0, t.f_in(10, 0));
}

TEST(Tree, evaluateNode) {
  Data data;
  TreeConfig tc;
  Tree t;
  Node node;
  Node feval;

  // setup
  tc.configure(FULL_METHOD, 2);
  data.load(TEST_SIMPLE_DATA);
  t.configure(&tc, data);

  node.setAsInput("x");
  node.nth_child = 0;
  t.prepData(data, node);

  node.setAsInput("y");
  node.nth_child = 1;
  t.prepData(data, node);

  // test add
  node.setAsBinaryFunc(ADD);
  t.evaluateNode(data, node, feval);
  ASSERT_FLOAT_EQ(2.0, feval.data(0));
  ASSERT_FLOAT_EQ(5.0, feval.data(1));
  ASSERT_FLOAT_EQ(8.0, feval.data(2));
  ASSERT_FLOAT_EQ(11.0, feval.data(3));

  // test sub
  node.setAsBinaryFunc(SUB);
  t.evaluateNode(data, node, feval);
  ASSERT_FLOAT_EQ(-2.0, feval.data(0));
  ASSERT_FLOAT_EQ(-3.0, feval.data(1));
  ASSERT_FLOAT_EQ(-4.0, feval.data(2));
  ASSERT_FLOAT_EQ(-5.0, feval.data(3));

  // test mul
  node.setAsBinaryFunc(MUL);
  t.evaluateNode(data, node, feval);
  ASSERT_FLOAT_EQ(0.0, feval.data(0));
  ASSERT_FLOAT_EQ(4.0, feval.data(1));
  ASSERT_FLOAT_EQ(12.0, feval.data(2));
  ASSERT_FLOAT_EQ(24.0, feval.data(3));
}

TEST(Tree, evaluate) {
  Data data;
  TreeConfig tc;
  Tree t;
  Node node;
  Node feval;

  // setup
  data.load(TEST_SINE_DATA);
  tc.configure(FULL_METHOD, 2);
  tc.inputs.push_back("x");
  t.configure(&tc, data);

  setupSineTree(t);
  t.update();
  t.printEquation();
  t.printStack();

  t.evaluate(data, "y");
  std::cout << t.error << std::endl;
}

TEST(Tree, toString) {
  Tree t;
  TreeConfig tc;
  Data data;

  tc.configure(FULL_METHOD, 2);
  data.load(TEST_SINE_DATA);
  t.configure(&tc, data);
  t.generate();
  t.toString();
}

TEST(Tree, printEquation) {
  Tree t;
  TreeConfig tc;
  Data data;

  tc.configure(FULL_METHOD, 2);
  data.load(TEST_SINE_DATA);
  t.configure(&tc, data);
  t.generate();
  t.printEquation();
}

}  // end of gp namespace
}  // end of yarl namespace
