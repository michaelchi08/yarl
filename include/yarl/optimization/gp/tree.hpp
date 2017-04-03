#ifndef YARL_OPTIMIZATION_GP_TREE_HPP
#define YARL_OPTIMIZATION_GP_TREE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/gp/data.hpp"
#include "yarl/optimization/gp/metric.hpp"


namespace yarl {
namespace gp {

// ERROR MESSAGES
#define E_FSET_NO_UNARY "function set has no unary function!"
#define E_FSET_NO_BINARY "function set has no binary function!"
#define E_NODE_TYPE "invalid node type: %d\n"
#define E_POPULATION "population is NULL!"
#define E_POPULATION_EMPTY "population is empty!"
#define E_SELECTED "selected is NULL!"
#define E_NUM_OF_INDIVIDUALS "invalid number of individuals!"
#define E_SELECTION "selection_config is NULL!"
#define E_SELECTION_FAILED "selection is failed!"
#define E_SELECTION_FUNCTION "selection function is NULL!"
#define E_SELECTION_CONFIG "selection config is NULL!"
#define E_TOURNAMENT_SIZE "invalid tournament selection size!"

// CONSTANTS
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FULL_METHOD 1
#define GROW_METHOD 2
#define RHAH_METHOD 3

#define UINITI -1
#define UINITF FLT_MAX
#define UINITC '\0'

#define CONST 1
#define INPUT 2
#define UFUNC 3
#define BFUNC 4
#define FEVAL 5

#define ADD 10
#define SUB 11
#define MUL 12
#define DIV 13
#define POW 14
#define LOG 15
#define EXP 16
#define RAD 17
#define SIN 18
#define COS 19

class Node {
public:
  // general
  int type;
  Node *parent;
  int nth_child;

  // constant
  double nval;

  // input
  std::string input;

  // function
  int fval;
  int arity;
  std::vector<Node> children;

  // evaluation
  VecX data;

  Node(void);
  void setAsConstant(double constant);
  void setAsInput(std::string input);
  void setAsUnaryFunc(int function_type);
  void setAsBinaryFunc(int function_type);
  bool isTermNode(void);
  bool isFuncNode(void);
  int copyFrom(Node &target);
  int deepCopyFrom(Node &target);
  int equals(Node &target);
  int deepEquals(Node &target);
  std::string toString(void);
  void print(void);
};

class FunctionSet {
public:
  bool configured;

  std::vector<int> unary_functions;
  std::vector<int> binary_functions;

  FunctionSet(void);
  int configure(void);
  void clear(void);
  Node randomUnaryFunction(void);
  Node randomBinaryFunction(void);
  Node randomFunction(void);
};

class TerminalSet {
public:
  bool configured;

  std::vector<double> constants;
  std::vector<std::string> inputs;

  TerminalSet(void);
  int configure(void);
  void clear(void);
  Node randomInput(void);
  Node randomConstant(void);
  Node randomTerminal(void);
};

class TreeConfig {
public:
  int build_method;
  int max_depth;

  FunctionSet fs;
  TerminalSet ts;
};

class Tree {
public:
  Node root;
  std::vector<Node> chromosome;

  int nb_inputs;
  int nb_constants;
  int nb_functions;

  int size;
  int depth;

  double error;
  double score;
  int hits;
  int evaluated;

  FunctionSet fs;
  TerminalSet ts;

  Tree(void);
  void clear(void);
  int copyFrom(Tree &t);
  void updateTraverse(Node &node, int depth);
  void update(void);
  void build(int method, Node &node, int depth, int max_depth);
  int generate(void);
  int evaluate(void);
  void print(void);
  std::string toString(void);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
