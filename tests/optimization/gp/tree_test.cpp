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
  EXPECT_EQ(5, (int) tc.unary_functions.size());
  EXPECT_EQ(5, (int) tc.binary_functions.size());
  EXPECT_EQ(11, (int) tc.constants.size());
  EXPECT_EQ(0, (int) tc.inputs.size());
}

TEST(TreeConfig, randomUnaryFunction) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomUnaryFunction(node);
    EXPECT_EQ(0, retval);
    EXPECT_EQ(UFUNC, node.type);
    EXPECT_EQ(1, node.arity);
  }
}

TEST(TreeConfig, randomBinaryFunction) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomBinaryFunction(node);
    EXPECT_EQ(0, retval);
    EXPECT_EQ(BFUNC, node.type);
    EXPECT_EQ(2, node.arity);
  }
}

TEST(TreeConfig, randomFunction) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomFunction(node);
    EXPECT_EQ(0, retval);
    EXPECT_TRUE(node.type == UFUNC || node.type == BFUNC);
    EXPECT_TRUE(node.arity == 1 || node.arity == 2);
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
    EXPECT_EQ(0, retval);
    EXPECT_EQ(INPUT, node.type);
  }
}

TEST(TreeConfig, randomConstant) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomConstant(node);
    EXPECT_EQ(0, retval);
    EXPECT_EQ(CONST, node.type);
  }
}

TEST(TreeConfig, randomTerminal) {
  int retval;
  TreeConfig tc;
  Node node;

  tc.configure(FULL_METHOD, 2);
  for (int i = 0; i < 10; i++) {
    retval = tc.randomTerminal(node);
    EXPECT_EQ(0, retval);
    EXPECT_TRUE(node.type == INPUT || node.type == CONST);
  }
}

TEST(Tree, constructor) {
  Tree tree;

  EXPECT_EQ(0, (int) tree.chromosome.size());

  EXPECT_EQ(0, tree.nb_inputs);
  EXPECT_EQ(0, tree.nb_constants);
  EXPECT_EQ(0, tree.nb_functions);

  EXPECT_EQ(0, tree.size);
  EXPECT_EQ(0, tree.depth);

  EXPECT_EQ(0, tree.error);
  EXPECT_EQ(0, tree.score);
  EXPECT_EQ(0, tree.hits);
  EXPECT_EQ(0, tree.evaluated);
}

TEST(Tree, configure) {
  Tree tree;
  TreeConfig tc;

  tree.configure(&tc);
  EXPECT_EQ(0, (int) tree.chromosome.size());

  EXPECT_TRUE(&tc == tree.tc);
}

TEST(Tree, clear) {
  Tree tree;
  TreeConfig tc;

  tree.configure(&tc);
  tree.clear();
  EXPECT_EQ(0, (int) tree.chromosome.size());

  EXPECT_EQ(0, tree.nb_inputs);
  EXPECT_EQ(0, tree.nb_constants);
  EXPECT_EQ(0, tree.nb_functions);

  EXPECT_EQ(0, tree.size);
  EXPECT_EQ(0, tree.depth);

  EXPECT_EQ(0, tree.error);
  EXPECT_EQ(0, tree.score);
  EXPECT_EQ(0, tree.hits);
  EXPECT_EQ(0, tree.evaluated);
}

TEST(Tree, copyFrom) {
  Tree t1, t2;
  std::string s;

  setupSineTree(t1);
  t2.copyFrom(t1);

  s = t2.root->toString();
  EXPECT_EQ("F[SIN]", s);

  s = t2.root->children[0]->children[0]->toString();
  EXPECT_EQ("F[RAD]", s);

  s = t2.root->children[0]->toString();
  EXPECT_EQ("F[MUL]", s);

  s = t2.root->children[0]->children[0]->children[0]->toString();
  EXPECT_EQ("T[100]", s);

  s = t2.root->children[0]->children[1]->toString();
  EXPECT_EQ("T[x]", s);
}

TEST(Tree, update) {
  Tree t;

  setupSineTree(t);
  t.update();

  EXPECT_EQ(5, (int) t.chromosome.size());
  EXPECT_EQ("T[100]", t.chromosome[0]->toString());
  EXPECT_EQ("F[RAD]", t.chromosome[1]->toString());
  EXPECT_EQ("T[x]", t.chromosome[2]->toString());
  EXPECT_EQ("F[MUL]", t.chromosome[3]->toString());
  EXPECT_EQ("F[SIN]", t.chromosome[4]->toString());
}

TEST(Tree, generate) {
  Tree t;
  TreeConfig tc;

  tc.configure(FULL_METHOD, 2);
  t.configure(&tc);
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
  t.configure(&tc);
  t.f_in = MatX(data.rows, 2);
  t.f_out = VecX(data.rows);

  // prep input data
  node.setAsInput("x");
  node.nth_child = 0;
  t.prepData(data, node);
  EXPECT_FLOAT_EQ(0.0, t.f_in(0, 0));
  EXPECT_FLOAT_EQ(10.0, t.f_in(10, 0));

  // prep const data
  node.setAsConstant(23.0);
  node.nth_child = 0;
  t.prepData(data, node);
  EXPECT_FLOAT_EQ(23.0, t.f_in(10, 0));

  // prep feval data
  node.type = FEVAL;
  node.nth_child = 0;
  node.data = VecX(data.rows);
  for (int i = 0; i < data.rows; i++) {
    node.data(i) = 23.0;
  }
  t.prepData(data, node);
  EXPECT_FLOAT_EQ(23.0, t.f_in(10, 0));
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
  t.configure(&tc);
  t.f_in = MatX(data.rows, 2);
  t.f_out = VecX(data.rows);

  node.setAsInput("x");
  node.nth_child = 0;
  t.prepData(data, node);

  node.setAsInput("y");
  node.nth_child = 1;
  t.prepData(data, node);

  // test add
  node.setAsBinaryFunc(ADD);
  t.evaluateNode(data, node, feval);
  EXPECT_FLOAT_EQ(2.0, feval.data(0));
  EXPECT_FLOAT_EQ(5.0, feval.data(1));
  EXPECT_FLOAT_EQ(8.0, feval.data(2));
  EXPECT_FLOAT_EQ(11.0, feval.data(3));

  // test sub
  node.setAsBinaryFunc(SUB);
  t.evaluateNode(data, node, feval);
  EXPECT_FLOAT_EQ(-2.0, feval.data(0));
  EXPECT_FLOAT_EQ(-3.0, feval.data(1));
  EXPECT_FLOAT_EQ(-4.0, feval.data(2));
  EXPECT_FLOAT_EQ(-5.0, feval.data(3));

  // test mul
  node.setAsBinaryFunc(MUL);
  t.evaluateNode(data, node, feval);
  EXPECT_FLOAT_EQ(0.0, feval.data(0));
  EXPECT_FLOAT_EQ(4.0, feval.data(1));
  EXPECT_FLOAT_EQ(12.0, feval.data(2));
  EXPECT_FLOAT_EQ(24.0, feval.data(3));
}

TEST(Tree, evaluateTraverse) {
  Tree t;
  Data data;

  // setup
  data.load(TEST_SINE_DATA);

  Node *n1 = new Node();
  Node *n2 = new Node();
  Node *n3 = new Node();
  Node *n4 = new Node();

  n1->setAsBinaryFunc(DIV);
  n2->setAsConstant(1.0);
  n3->setAsUnaryFunc(LOG);
  n4->setAsConstant(0.0);

  n1->children[0] = n2;
  n1->children[1] = n3;

  n3->children[0] = n4;

  t.root = n1;
  t.f_in = MatX(data.rows, 2);
  t.f_out = VecX(data.rows);
  t.update();

  // test
  Node result;
  t.evaluateTraverse(data, result);
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
  t.configure(&tc);

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
  t.configure(&tc);
  t.generate();
  t.toString();
}

TEST(Tree, printEquation) {
  Tree t;
  TreeConfig tc;
  Data data;

  tc.configure(FULL_METHOD, 2);
  data.load(TEST_SINE_DATA);
  t.configure(&tc);
  t.generate();
  t.printEquation();
}

}  // end of gp namespace
}  // end of yarl namespace
