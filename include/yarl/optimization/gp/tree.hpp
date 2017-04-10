#ifndef YARL_OPTIMIZATION_GP_TREE_HPP
#define YARL_OPTIMIZATION_GP_TREE_HPP

#include <stack>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/gp/node.hpp"
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

class TreeConfig {
public:
  int build_method;
  int max_depth;

  // function set
  std::vector<int> unary_functions;
  std::vector<int> binary_functions;

  // terminal set
  std::vector<double> constants;
  std::vector<std::string> inputs;

  TreeConfig(void);
  int configure(int build_method, int max_depth);
  void clear(void);
  int randomUnaryFunction(Node &node);
  int randomBinaryFunction(Node &node);
  int randomFunction(Node &node);
  int randomInput(Node &node);
  int randomConstant(Node &node);
  int randomTerminal(Node &node);
};

class Tree {
public:
  Node *root;
  std::vector<Node *> chromosome;

  int nb_inputs;
  int nb_constants;
  int nb_functions;

  int size;
  int depth;

  double error;
  double score;
  int hits;
  int evaluated;

  MatX f_in;
  VecX f_out;

  TreeConfig *tc;

  Tree(void);
  ~Tree(void);
  int configure(TreeConfig *tc, Data *data);
  void clear(void);
  int copyFrom(Tree &t);
  void updateTraverse(Node *node, int depth);
  void update(void);
  int build(int method, Node &node, int depth);
  int generate(void);
  int prepData(const Data &data, const Node &node);
  int evaluateNode(const Data &d, const Node &n, Node &feval);
  int evaluateTraverse(const Data &d, Node &result);
  int evaluate(const Data &d, const std::string predict);
  std::string toString(void);
  void printEquation(void);
  void printStack(void);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
