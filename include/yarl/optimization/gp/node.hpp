#ifndef YARL_OPTIMIZATION_GP_NODE_HPP
#define YARL_OPTIMIZATION_GP_NODE_HPP

#include <memory>

#include "yarl/utils/utils.hpp"

namespace yarl {
namespace gp {

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
  std::array<Node *, 2> children;

  // evaluation
  VecX data;

  Node(void);
  ~Node(void);
  void setAsConstant(double constant);
  void setAsInput(std::string input);
  void setAsFuncEval(int length);
  void setAsUnaryFunc(int function_type);
  void setAsBinaryFunc(int function_type);
  bool isTermNode(void);
  bool isFuncNode(void);
  int copyFrom(Node &target);
  int deepCopyFrom(Node &target);
  bool equals(Node &target);
  bool deepEquals(Node &target);
  std::string toString(void);
  void print(void);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif