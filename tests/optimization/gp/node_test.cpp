#include "yarl/test.hpp"
#include "yarl/optimization/gp/node.hpp"

namespace yarl {
namespace gp {

TEST(Node, constructor) {
  Node node;

  ASSERT_EQ(UINITI, node.type);
  ASSERT_EQ(NULL, node.parent);
  ASSERT_EQ(UINITI, node.nth_child);

  ASSERT_EQ(UINITI, node.nval);

  ASSERT_EQ("", node.input);

  ASSERT_EQ(UINITI, node.fval);
  ASSERT_EQ(UINITI, node.arity);
  ASSERT_TRUE(node.children[0] == NULL);
  ASSERT_TRUE(node.children[1] == NULL);
}

TEST(Node, setAsConstant) {
  Node node;

  node.setAsConstant(1.0);
  ASSERT_EQ(CONST, node.type);
  ASSERT_EQ(NULL, node.parent);
  ASSERT_EQ(UINITI, node.nth_child);

  ASSERT_EQ(1.0, node.nval);

  ASSERT_EQ("", node.input);

  ASSERT_EQ(UINITI, node.fval);
  ASSERT_EQ(UINITI, node.arity);
  ASSERT_TRUE(node.children[0] == NULL);
  ASSERT_TRUE(node.children[1] == NULL);
}

TEST(Node, setAsInput) {
  Node node;

  node.setAsInput("x");
  ASSERT_EQ(INPUT, node.type);
  ASSERT_EQ(NULL, node.parent);
  ASSERT_EQ(UINITI, node.nth_child);

  ASSERT_EQ(UINITI, node.nval);

  ASSERT_EQ("x", node.input);

  ASSERT_EQ(UINITI, node.fval);
  ASSERT_EQ(UINITI, node.arity);
  ASSERT_TRUE(node.children[0] == NULL);
  ASSERT_TRUE(node.children[1] == NULL);
}

TEST(Node, setAsFuncEval) {
  Node node;

  node.setAsFuncEval(10);
  ASSERT_EQ(FEVAL, node.type);
  ASSERT_EQ(NULL, node.parent);
  ASSERT_EQ(UINITI, node.nth_child);

  ASSERT_EQ(UINITI, node.nval);

  ASSERT_EQ("", node.input);

  ASSERT_EQ(UINITI, node.fval);
  ASSERT_EQ(UINITI, node.arity);
  ASSERT_TRUE(node.children[0] == NULL);
  ASSERT_TRUE(node.children[1] == NULL);

  ASSERT_EQ(10, node.data.size());
}

TEST(Node, setAsUnaryFunc) {
  Node node;

  node.setAsUnaryFunc(LOG);
  ASSERT_EQ(UFUNC, node.type);
  ASSERT_EQ(NULL, node.parent);
  ASSERT_EQ(UINITI, node.nth_child);

  ASSERT_EQ(UINITI, node.nval);

  ASSERT_EQ("", node.input);

  ASSERT_EQ(LOG, node.fval);
  ASSERT_EQ(1, node.arity);
  ASSERT_TRUE(node.children[0] == NULL);
  ASSERT_TRUE(node.children[1] == NULL);
}

TEST(Node, setAsBinaryFunc) {
  Node node;

  node.setAsBinaryFunc(POW);
  ASSERT_EQ(BFUNC, node.type);
  ASSERT_EQ(NULL, node.parent);
  ASSERT_EQ(UINITI, node.nth_child);

  ASSERT_EQ(UINITI, node.nval);

  ASSERT_EQ("", node.input);

  ASSERT_EQ(POW, node.fval);
  ASSERT_EQ(2, node.arity);
  ASSERT_TRUE(node.children[0] == NULL);
  ASSERT_TRUE(node.children[1] == NULL);
}

TEST(Node, isTermNode) {
  Node node;

  node.setAsConstant(1.0);
  ASSERT_TRUE(node.isTermNode());

  node.setAsInput("x");
  ASSERT_TRUE(node.isTermNode());

  node.setAsFuncEval(10);
  ASSERT_TRUE(node.isTermNode());

  node.setAsUnaryFunc(LOG);
  ASSERT_FALSE(node.isTermNode());

  node.setAsBinaryFunc(ADD);
  ASSERT_FALSE(node.isTermNode());
}

TEST(Node, isFuncNode) {
  Node node;

  node.setAsConstant(1.0);
  ASSERT_FALSE(node.isFuncNode());

  node.setAsInput("x");
  ASSERT_FALSE(node.isFuncNode());

  node.setAsFuncEval(10);
  ASSERT_FALSE(node.isFuncNode());

  node.setAsUnaryFunc(LOG);
  ASSERT_TRUE(node.isFuncNode());

  node.setAsBinaryFunc(ADD);
  ASSERT_TRUE(node.isFuncNode());
}

TEST(Node, copyFrom) {
  Node src;
  Node copy;

  // test copy constant node
  src.setAsConstant(2.0);
  copy.copyFrom(src);

  ASSERT_EQ(CONST, copy.type);
  ASSERT_EQ(NULL, copy.parent);
  ASSERT_EQ(UINITI, copy.nth_child);
  ASSERT_FLOAT_EQ(src.nval, copy.nval);

  // test copy input node
  src.setAsInput("x");
  copy.copyFrom(src);

  ASSERT_EQ(INPUT, copy.type);
  ASSERT_EQ(NULL, copy.parent);
  ASSERT_EQ(UINITI, copy.nth_child);
  ASSERT_EQ(src.input, copy.input);

  // test copy feval node
  src.setAsFuncEval(10);
  copy.copyFrom(src);

  ASSERT_EQ(FEVAL, copy.type);
  ASSERT_EQ(NULL, copy.parent);
  ASSERT_EQ(UINITI, copy.nth_child);
  ASSERT_EQ(src.data.size(), copy.data.size());

  // test copy unary function node
  src.setAsUnaryFunc(LOG);
  copy.copyFrom(src);

  ASSERT_EQ(UFUNC, copy.type);
  ASSERT_EQ(NULL, copy.parent);
  ASSERT_EQ(UINITI, copy.nth_child);
  ASSERT_EQ(src.fval, copy.fval);
  ASSERT_EQ(src.arity, copy.arity);

  // test copy binary function node
  src.setAsBinaryFunc(POW);
  copy.copyFrom(src);

  ASSERT_EQ(BFUNC, copy.type);
  ASSERT_EQ(NULL, copy.parent);
  ASSERT_EQ(UINITI, copy.nth_child);
  ASSERT_EQ(src.fval, copy.fval);
  ASSERT_EQ(src.arity, copy.arity);
}

TEST(Node, deepCopyFrom) {
  Node n;
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

  n.deepCopyFrom(*n1);
  ASSERT_TRUE(n.deepEquals(*n1));

  delete n1;
}

TEST(Node, equals) {
  Node x;
  Node y;

  // test constant node
  x.setAsConstant(1);
  y.setAsConstant(1);
  ASSERT_TRUE(x.equals(y));

  x.setAsConstant(1);
  y.setAsConstant(2);
  ASSERT_FALSE(x.equals(y));

  // test input node
  x.setAsInput("x");
  y.setAsInput("x");
  ASSERT_TRUE(x.equals(y));

  x.setAsInput("x");
  y.setAsInput("y");
  ASSERT_FALSE(x.equals(y));

  // test feval node
  x.setAsFuncEval(3);
  y.setAsFuncEval(3);
  x.data << 1, 2, 3;
  y.data << 1, 2, 3;
  ASSERT_TRUE(x.equals(y));

  x.setAsFuncEval(3);
  y.setAsFuncEval(3);
  x.data << 1, 2, 3;
  y.data << 1, 2, 1;
  ASSERT_FALSE(x.equals(y));

  // test unary function node
  x.setAsUnaryFunc(LOG);
  y.setAsUnaryFunc(LOG);
  ASSERT_TRUE(x.equals(y));

  x.setAsUnaryFunc(LOG);
  y.setAsUnaryFunc(EXP);
  ASSERT_FALSE(x.equals(y));

  // test binary function node
  x.setAsBinaryFunc(ADD);
  y.setAsBinaryFunc(ADD);
  ASSERT_TRUE(x.equals(y));

  x.setAsBinaryFunc(ADD);
  y.setAsBinaryFunc(SUB);
  ASSERT_FALSE(x.equals(y));
}

TEST(Node, toString) {
  Node node;

  node.setAsConstant(1);
  ASSERT_EQ("T[1]", node.toString());

  node.setAsInput("x");
  ASSERT_EQ("T[x]", node.toString());

  node.setAsUnaryFunc(LOG);
  ASSERT_EQ("F[LOG]", node.toString());

  node.setAsBinaryFunc(ADD);
  ASSERT_EQ("F[ADD]", node.toString());
}

TEST(Node, print) {
  Node node;

  node.setAsConstant(1);
  node.print();

  node.setAsInput("x");
  node.print();

  node.setAsUnaryFunc(LOG);
  node.print();

  node.setAsBinaryFunc(ADD);
  node.print();
}

}  // end of gp namespace
}  // end of yarl namespace
