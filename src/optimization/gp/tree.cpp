#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

TreeConfig::TreeConfig(void) {
  this->build_method = UINITI;
  this->max_depth = UINITI;

  this->unary_functions.clear();
  this->binary_functions.clear();
  this->constants.clear();
}

int TreeConfig::configure(int build_method, int max_depth) {
  // build parameters
  this->build_method = build_method;
  this->max_depth = max_depth;

  // function set
  this->unary_functions.push_back(LOG);
  this->unary_functions.push_back(EXP);
  this->unary_functions.push_back(RAD);
  this->unary_functions.push_back(SIN);
  this->unary_functions.push_back(COS);

  this->binary_functions.push_back(ADD);
  this->binary_functions.push_back(SUB);
  this->binary_functions.push_back(MUL);
  this->binary_functions.push_back(DIV);
  this->binary_functions.push_back(POW);

  // terminal set
  this->constants.push_back(0.0);
  this->constants.push_back(1.0);
  this->constants.push_back(2.0);
  this->constants.push_back(3.0);
  this->constants.push_back(4.0);
  this->constants.push_back(5.0);
  this->constants.push_back(6.0);
  this->constants.push_back(7.0);
  this->constants.push_back(8.0);
  this->constants.push_back(9.0);
  this->constants.push_back(10.0);

  return 0;
}

int TreeConfig::randomUnaryFunction(Node &node) {
  int index;

  // pre-check
  if (this->unary_functions.size() == 0) {
    return -1;
  }

  // random unary function
  index = randi(0, (int) this->unary_functions.size() - 1);
  node.setAsUnaryFunc(this->unary_functions[index]);

  return 0;
}

int TreeConfig::randomBinaryFunction(Node &node) {
  int index;

  // pre-check
  if (this->binary_functions.size() == 0) {
    return -1;
  }

  // random binary function
  index = randi(0, (int) this->binary_functions.size() - 1);
  node.setAsBinaryFunc(this->binary_functions[index]);

  return 0;
}

int TreeConfig::randomFunction(Node &node) {
  // pre-check
  if (this->unary_functions.size() == 0) {
    return this->randomBinaryFunction(node);
  } else if (this->binary_functions.size() == 0) {
    return this->randomUnaryFunction(node);
  }

  // return random function
  if (randf(0.0, 1.0) > 0.5) {
    return this->randomUnaryFunction(node);
  } else {
    return this->randomBinaryFunction(node);
  }
}

int TreeConfig::randomInput(Node &node) {
  int index;

  // pre-check
  if (this->inputs.size() == 0) {
    return -1;
  } else if (this->inputs.size() == 1) {
    node.setAsInput(this->inputs[0]);
    return 0;
  }

  // random input node
  index = randi(0, this->inputs.size() - 1);
  node.setAsInput(this->inputs[index]);

  return 0;
}

int TreeConfig::randomConstant(Node &node) {
  int index;

  // pre-check
  if (this->constants.size() == 0) {
    return -1;
  }

  // random constant node
  index = randi(0, this->constants.size() - 1);
  node.setAsConstant(this->constants[index]);

  return 0;
}

int TreeConfig::randomTerminal(Node &node) {
  // pre-check
  if (this->constants.size() == 0 && this->inputs.size() == 0) {
    return -1;
  }

  // return random terminal
  if (this->inputs.size() == 0) {
    return this->randomConstant(node);
  } else if (this->constants.size() == 0) {
    return this->randomInput(node);
  }

  if (randf(0.0, 1.0) > 0.5) {
    return this->randomInput(node);
  } else {
    return this->randomConstant(node);
  }

  return 0;
}

Tree::Tree(void) {
  this->root = NULL;
  this->chromosome.clear();

  this->nb_inputs = 0;
  this->nb_constants = 0;
  this->nb_functions = 0;

  this->size = 0;
  this->depth = 0;

  this->error = 0;
  this->score = 0;
  this->hits = 0;
  this->evaluated = 0;

  this->f_in = MatX();
  this->f_out = VecX();

  this->tc = NULL;
}

Tree::~Tree(void) {
  delete this->root;
}

int Tree::configure(TreeConfig *tc, Data *data) {
  this->root = NULL;
  this->chromosome.clear();

  this->nb_inputs = 0;
  this->nb_constants = 0;
  this->nb_functions = 0;

  this->size = 0;
  this->depth = 0;

  this->error = 0;
  this->score = 0;
  this->hits = 0;
  this->evaluated = 0;

  this->f_in = MatX(data->rows, 2);
  this->f_out = VecX(data->rows);

  this->tc = tc;

  return 0;
}

void Tree::clear(void) {
  this->root = NULL;
  this->chromosome.clear();

  this->nb_inputs = 0;
  this->nb_constants = 0;
  this->nb_functions = 0;

  this->size = 0;
  this->depth = 0;

  this->error = 0;
  this->score = 0;
  this->hits = 0;
  this->evaluated = 0;

  this->tc = NULL;
}

int Tree::copyFrom(const Tree &target) {
  if (this->root == NULL) {
    this->root = new Node();
  }
  this->root->deepCopyFrom(*target.root);

  this->nb_inputs = target.nb_inputs;
  this->nb_constants = target.nb_constants;
  this->nb_functions = target.nb_functions;

  this->size = target.size;
  this->depth = target.depth;

  this->error = target.error;
  this->score = target.score;
  this->hits = target.hits;
  this->evaluated = target.evaluated;

  this->tc = target.tc;

  return 0;
}

void Tree::updateTraverse(Node *node, int depth) {
  // pre-check
  if (depth > this->depth) {
    this->depth++;
  }

  // traverse
  if (node->isTermNode()) {
    this->chromosome.push_back(node);

  } else if (node->isFuncNode()) {
    for (int i = 0; i < node->arity; i++) {
      node->children[i]->parent = node;
      node->children[i]->nth_child = i;
      this->updateTraverse(node->children[i], depth + 1);
    }
    this->chromosome.push_back(node);
  }
}

void Tree::update(void) {
  // reset chromosome, size and depth
  this->chromosome.clear();
  this->depth = 0;

  // update tree
  this->updateTraverse(this->root, 0);
  this->size = this->chromosome.size();
}

int Tree::build(int method, Node &node, int depth) {
  Node *child;

  // pre-check
  if (depth > this->depth) {
    this->depth++;
  }

  // build tree
  for (int i = 0; i < node.arity; i++) {
    child = new Node();

    if ((depth + 1) == this->tc->max_depth) {
      // create terminal node
      this->tc->randomTerminal(*child);
      child->parent = &node;
      child->nth_child = i;
      node.children[i] = child;

    } else if (method == GROW_METHOD && randf(0.0, 1.0) > 0.8) {
      // create terminal node
      this->tc->randomTerminal(*child);
      child->parent = &node;
      child->nth_child = i;
      node.children[i] = child;

    } else {
      // create function node
      this->tc->randomFunction(*child);
      child->parent = &node;
      child->nth_child = i;
      node.children[i] = child;

      this->build(method, *child, depth + 1);
    }
  }

  return 0;
}

int Tree::generate(void) {
  Node *root;

  // setup
  root = new Node();
  this->tc->randomFunction(*root);
  this->root = root;

  // build tree
  switch (this->tc->build_method) {
    case FULL_METHOD: this->build(FULL_METHOD, *this->root, 0); break;
    case GROW_METHOD: this->build(GROW_METHOD, *this->root, 0); break;
    case RHAH_METHOD:
      if (randf(0.0, 1.0) > 0.5) {
        this->build(FULL_METHOD, *this->root, 0);
      } else {
        this->build(GROW_METHOD, *this->root, 0);
      }
      break;
  }

  // update
  this->update();

  return 0;
}

int Tree::prepData(const Data &data, const Node &node) {
  int data_index;

  if (node.type == INPUT) {
    data_index = data.fieldIndex(node.input);
    for (int i = 0; i < data.rows; i++) {
      this->f_in(i, node.nth_child) = data.data(i, data_index);
    }

  } else if (node.type == CONST) {
    for (int i = 0; i < data.rows; i++) {
      this->f_in(i, node.nth_child) = node.nval;
    }

  } else if (node.type == FEVAL) {
    for (int i = 0; i < data.rows; i++) {
      this->f_in(i, node.nth_child) = node.data(i);
    }

  } else {
    return -1;
  }

  return 0;
}

int Tree::evaluateNode(const Data &d, const Node &n, Node &feval) {
  double result;

  // setup
  feval.setAsFuncEval(d.rows);

  // evaluate
  switch (n.fval) {
    case ADD:
      for (int i = 0; i < d.rows; i++) {
        feval.data(i) = this->f_in(i, 0) + this->f_in(i, 1);
      }
      break;
    case SUB:
      for (int i = 0; i < d.rows; i++) {
        feval.data(i) = this->f_in(i, 0) - this->f_in(i, 1);
      }
      break;
    case MUL:
      for (int i = 0; i < d.rows; i++) {
        feval.data(i) = this->f_in(i, 0) * this->f_in(i, 1);
      }
      break;
    case DIV:
      for (int i = 0; i < d.rows; i++) {
        if (fltcmp(this->f_in(i, 1), 0.0) == 0) {
          goto eval_error;
        }
        feval.data(i) = this->f_in(i, 0) / this->f_in(i, 1);
      }
      break;
    case POW:
      for (int i = 0; i < d.rows; i++) {
        result = pow(this->f_in(i, 0), this->f_in(i, 1));
        if (std::isfinite(result)) {
          feval.data(i) = result;
        } else {
          goto eval_error;
        }
      }
      break;
    case EXP:
      for (int i = 0; i < d.rows; i++) {
        result = exp(this->f_in(i, 0));
        if (std::isfinite(result)) {
          feval.data(i) = result;
        } else {
          goto eval_error;
        }
      }
      break;
    case LOG:
      for (int i = 0; i < d.rows; i++) {
        result = log(this->f_in(i, 0));
        if (std::isfinite(result)) {
          feval.data(i) = result;
        } else {
          goto eval_error;
        }
      }
      break;
    case RAD:
      for (int i = 0; i < d.rows; i++) {
        feval.data(i) = this->f_in(i, 0) * (double) (M_PI / 180.0);
      }
      break;
    case SIN:
      for (int i = 0; i < d.rows; i++) {
        feval.data(i) = sin(this->f_in(i, 0));
      }
      break;
    case COS:
      for (int i = 0; i < d.rows; i++) {
        feval.data(i) = cos(this->f_in(i, 0));
      }
      break;
    default: log_err("Invalid function %d\n", n.type); exit(-1);
  }

  feval.nth_child = n.nth_child;  // keep track nth-child of node
  return 0;

eval_error:
  return -1;
}

int Tree::evaluateTraverse(const Data &d, Node &result) {
  std::stack<Node *> s;
  Node *n;
  Node *left;
  Node *right;
  Node *feval;

  // setup
  left = NULL;
  right = NULL;

  // evaluate tree
  for (size_t i = 0; i < this->chromosome.size(); i++) {
    n = this->chromosome[i];

    switch (n->type) {
      // terminal
      case CONST:
      case INPUT:
        s.push(this->chromosome[i]);
        break;

      // unary function
      case UFUNC:
        // pop from stack
        left = s.top();
        s.pop();

        // prepare data
        this->prepData(d, *left);
        if (left->type == FEVAL) {
          delete left;
        }

        // evaluate
        feval = new Node();
        this->evaluateNode(d, *n, *feval);
        s.push(feval);
        break;

      // binary function
      case BFUNC:
        // pop from stack
        right = s.top();
        s.pop();

        left = s.top();
        s.pop();

        // prepare data
        this->prepData(d, *left);
        this->prepData(d, *right);
        if (left->type == FEVAL) {
          delete left;
        }
        if (right->type == FEVAL) {
          delete right;
        }

        // evaluate
        feval = new Node();
        this->evaluateNode(d, *n, *feval);
        s.push(feval);
        break;
    }
  }
  result.copyFrom(*s.top());
  delete s.top();

  return 0;
}

int Tree::evaluate(const Data &d, const std::string predict) {
  int retval;
  Node result;

  // pre-check
  if (this->size < 3) {
    this->error = -FLT_MAX;
    this->score = -FLT_MAX;
    this->hits = 0;
    return -1;
  }

  // setup
  retval = this->evaluateTraverse(d, result);
  if (retval != 0) {
    this->error = -FLT_MAX;
    this->score = -FLT_MAX;
    this->hits = 0;
    return -2;
  }

  // caclulate error
  this->hits = 0;
  this->error = mse(d, predict, result.data);

  // calculate score
  this->score = -this->error - this->size;

  return 0;
}

static void equation_node(std::ostringstream &oss, Node &node) {
  switch (node.fval) {
    case ADD: oss << " + "; break;
    case SUB: oss << " - "; break;
    case MUL: oss << " * "; break;
    case DIV: oss << " / "; break;
    case POW: oss << "**"; break;
    case LOG: oss << "log"; break;
    case EXP: oss << "exp"; break;
    case RAD: oss << "rad"; break;
    case SIN: oss << "sin"; break;
    case COS: oss << "cos"; break;
  }
}

static void traverse_equation(std::ostringstream &oss, Node &node) {
  if (node.isTermNode()) {
    if (node.type == CONST) {
      oss << node.nval;
    } else if (node.type == INPUT) {
      oss << node.input;
    }

  } else if (node.type == UFUNC) {
    oss << "(";
    equation_node(oss, node);
    oss << "(";
    traverse_equation(oss, *node.children[0]);
    oss << ")";
    oss << ")";

  } else if (node.type == BFUNC) {
    oss << "(";
    traverse_equation(oss, *node.children[0]);
    equation_node(oss, node);
    traverse_equation(oss, *node.children[1]);
    oss << ")";
  }
}

std::string Tree::toString(void) {
  std::ostringstream oss;
  traverse_equation(oss, *this->root);
  return oss.str();
}

void Tree::printEquation(void) {
  std::cout << this->toString();
  std::cout << std::endl;
}

void Tree::printStack(void) {
  for (size_t i = 0; i < this->chromosome.size(); i++) {
    this->chromosome[i]->print();
  }
}

}  // end of gp namespace
}  // end of yarl namespace
