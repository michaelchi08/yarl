#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

Node::Node(void) {
  // general
  this->type = UINITI;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children.clear();

  // evaluation
  this->data = VecX();
}

void Node::setAsConstant(double constant) {
  // general
  this->type = CONST;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = constant;

  // input
  this->input = "";

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children.clear();

  // evaluation
  this->data = VecX();
}

void Node::setAsInput(std::string input) {
  // general
  this->type = INPUT;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children.clear();

  // evaluation
  this->data = VecX();
}

void Node::setAsUnaryFunc(int function_type) {
  // general
  this->type = UFUNC;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = function_type;
  this->arity = 1;
  this->children.clear();

  // evaluation
  this->data = VecX();
}

void Node::setAsBinaryFunc(int function_type) {
  // general
  this->type = BFUNC;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = function_type;
  this->arity = 2;
  this->children.clear();

  // evaluation
  this->data = VecX();
}

bool Node::isTermNode(void) {
  if (this->type == CONST || this->type == INPUT || this->type == FEVAL) {
    return true;
  } else {
    return false;
  }
}

bool Node::isFuncNode(void) {
  if (this->type == UFUNC || this->type == BFUNC) {
    return true;
  } else {
    return false;
  }
}

int Node::copyFrom(Node &target) {
  // general
  this->type = target.type;
  this->parent = target.parent;
  this->nth_child = target.nth_child;

  // constant
  if (target.type == CONST) {
    this->nval = target.nval;
  }

  // input
  if (target.type == INPUT) {
    this->input = target.input;
  }

  // function
  if (target.type == UFUNC || target.type == BFUNC) {
    this->fval = target.fval;
    this->arity = target.arity;

    // this function does not copy the children, if you want that
    // use node_deepcopy() instead
  }

  // evaluation
  if (target.type == FEVAL) {
    this->data = target.data;
  }

  return 0;
}

int Node::deepCopyFrom(Node &target) {
  // general
  this->type = target.type;
  this->parent = target.parent;
  this->nth_child = target.nth_child;

  // constant
  if (target.type == CONST) {
    this->nval = target.nval;
  }

  // input
  if (target.type == INPUT) {
    this->input = target.input;
  }

  // function
  if (target.type == UFUNC || target.type == BFUNC) {
    this->fval = target.fval;
    this->arity = target.arity;

    for (int i = 0; i < target.arity; i++) {
      this->children.push_back(target.children[i]);
    }
  }

  // evaluation
  if (target.type == FEVAL) {
    this->data = target.data;
  }

  return 0;
}

int Node::equals(Node &target) {
  // pre-check
  if (this->type != target.type) {
    return 0;
  }

  // constant
  if (this->type == CONST) {
    if (fltcmp(this->nval, target.nval) != 0) {
      return 0;
    }
  }

  // input
  if (this->type == INPUT) {
    if (this->input.compare(target.input) != 0) {
      return 0;
    }
  }

  // function
  if (this->type == UFUNC || target.type == BFUNC) {
    if (this->fval != target.fval) {
      return 0;
    } else if (this->arity != target.arity) {
      return 0;
    }
  }

  // evaluation
  if (this->type == FEVAL) {
    for (int i = 0; i < this->data.size(); i++) {
      if (fltcmp(this->data[i], target.data[i]) != 0) {
        return 0;
      }
    }
  }

  return 1;
}

int Node::deepEquals(Node &target) {
  int retval;

  if (this->isTermNode() && target.isTermNode()) {
    return this->equals(target);

  } else if (this->isFuncNode() && target.isFuncNode()) {
    if (this->equals(target) == 0) {
      return 0;
    }

    for (int i = 0; i < this->arity; i++) {
      retval = this->children[i].deepEquals(target.children[i]);
      if (retval == 0) {
        return 0;
      }
    }
  }

  return 1;
}

std::string Node::toString(void) {
  std::ostringstream oss;

  // build node string
  if (this->type == CONST) {
    oss << "T[" << this->nval << "]";

  } else if (this->type == INPUT) {
    oss << "T[" << this->input << "]";

  } else if (this->type == UFUNC || this->type == BFUNC) {
    oss << "F[" << this->fval << "]";
  }

  // copy and return node string
  return oss.str();
}

void Node::print(void) {
  if (this->type == CONST) {
    std::cout << "T[" << this->nval << "]";
  } else if (this->type == INPUT) {
    std::cout << "T[" << this->input << "]";
  } else if (this->type == UFUNC || this->type == BFUNC) {
    std::cout << "F[" << this->fval << "]";
  }
}

int FunctionSet::configure(void) {
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

  return 0;
}

void FunctionSet::clear(void) {
  this->unary_functions.clear();
  this->binary_functions.clear();
}

Node FunctionSet::randomUnaryFunction(void) {
  int index;
  Node node;

  index = randi(0, (int) this->unary_functions.size() - 1);
  node.setAsUnaryFunc(this->unary_functions[index]);

  return node;
}

Node FunctionSet::randomBinaryFunction(void) {
  int index;
  Node node;

  index = randi(0, (int) this->binary_functions.size() - 1);
  node.setAsUnaryFunc(this->binary_functions[index]);

  return node;
}

Node FunctionSet::randomFunction(void) {
  // pre-check
  if (this->unary_functions.size() == 0) {
    return this->randomBinaryFunction();
  } else if (this->binary_functions.size() == 0) {
    return this->randomUnaryFunction();
  }

  // return random function
  if (randf(0.0, 1.0) > 0.5) {
    return this->randomUnaryFunction();
  } else {
    return this->randomBinaryFunction();
  }
}


int TerminalSet::configure(void) {
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

void TerminalSet::clear(void) {
  this->constants.clear();
  this->inputs.clear();
}

Node TerminalSet::randomInput(void) {
  int index;
  Node node;

  index = randi(0, this->inputs.size() - 1);
  node.setAsInput(this->inputs[index]);

  return node;
}

Node TerminalSet::randomConstant(void) {
  int index;
  Node node;

  index = randi(0, this->constants.size() - 1);
  node.setAsConstant(this->constants[index]);

  return node;
}

Node TerminalSet::randomTerminal(void) {
  Node node;

  // pre-check
  if (this->inputs.size() == 0) {
    return this->randomConstant();
  } else if (this->constants.size() == 0) {
    return this->randomInput();
  }

  // return random terminal
  if (randf(0.0, 1.0) > 0.5) {
    return this->randomInput();
  } else {
    return this->randomConstant();
  }

  return node;
}

Tree::Tree(void) {
  this->root = Node();
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

  this->fs = FunctionSet();
  this->ts = TerminalSet();
}

void Tree::clear(void) {
  this->root = Node();
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

  this->fs = FunctionSet();
  this->ts = TerminalSet();
}

int Tree::copyFrom(Tree &target) {
  this->root.deepCopyFrom(target.root);

  this->nb_inputs = target.nb_inputs;
  this->nb_constants = target.nb_constants;
  this->nb_functions = target.nb_functions;

  this->size = target.size;
  this->depth = target.depth;

  this->error = target.error;
  this->score = target.score;
  this->hits = target.hits;
  this->evaluated = target.evaluated;

  this->evaluated = target.evaluated;

  this->fs = target.fs;
  this->ts = target.ts;

  return 0;
}

void Tree::updateTraverse(Node &node, int depth) {
  // pre-check
  if (depth > this->depth) {
    this->depth++;
  }

  // traverse
  if (node.isTermNode()) {
    this->chromosome.push_back(node);

  } else if (node.isFuncNode()) {
    for (int i = 0; i < node.arity; i++) {
      node.children[i].parent = &node;
      node.children[i].nth_child = i;
      this->updateTraverse(node.children[i], depth + 1);
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
  this->chromosome.push_back(this->root);
}

void Tree::build(int method, Node &node, int depth, int max_depth) {
  Node child;

  // pre-check
  if (depth > this->depth) {
    this->depth++;
  }

  // grow method
  for (int i = 0; i < node.arity; i++) {
    if ((depth + 1) == max_depth) {
      // create terminal node
      child = this->ts.randomTerminal();
      child.parent = &node;
      child.nth_child = i;
      node.children[i] = child;

    } else if (method == GROW_METHOD && randf(0.0, 1.0) > 0.8) {
      // create terminal node
      child = this->ts.randomTerminal();
      child.parent = &node;
      child.nth_child = i;
      node.children[i] = child;

    } else {
      // create function node
      child = this->fs.randomFunction();
      child.parent = &node;
      child.nth_child = i;
      node.children[i] = child;

      this->build(method, child, depth + 1, max_depth);
    }
  }
}

// void tree_generate(struct tree *t, struct tree_config *tc) {
//   // setup
//   tree_setup(t);
//   t->fs = tc->fs;
//   t->ts = tc->ts;
//   t->root = node_random_func(tc->fs);
//
//   // build tree
//   switch (tc->build_method) {
//   case FULL_METHOD:
//     tree_build(FULL_METHOD, t, t->root, 0, tc->max_depth);
//     break;
//
//   case GROW_METHOD:
//     tree_build(GROW_METHOD, t, t->root, 0, tc->max_depth);
//     break;
//
//   case RHAH_METHOD:
//     if (randf(0.0, 1.0) > 0.5) {
//       tree_build(FULL_METHOD, t, t->root, 0, tc->max_depth);
//     } else {
//       tree_build(GROW_METHOD, t, t->root, 0, tc->max_depth);
//     }
//     break;
//   }
//
//   tree_update(t);
// }
//
// int tree_prep_data(struct node *n, struct data *d) {
//   int i;
//   int data_index;
//
//   if (n->type == INPUT) {
//     data_index = data_field_index(d, n->input);
//     for (i = 0; i < d->rows; i++) {
//       d->f_in[n->nth_child][i] = d->data[data_index][i];
//     }
//
//   } else if (n->type == CONST) {
//     for (i = 0; i < d->rows; i++) {
//       d->f_in[n->nth_child][i] = n->nval;
//     }
//
//   } else if (n->type == FEVAL) {
//     for (i = 0; i < d->rows; i++) {
//       d->f_in[n->nth_child][i] = n->data[i];
//     }
//
//   } else {
//     return -1;
//   }
//
//   return 0;
// }
//
// float tree_halstead_metric(struct tree *t) {
//   int i;
//   char *ns;
//   struct node *n;
//   struct halstead_metric m;
//   struct hashmap *operators;
//   struct hashmap *operands;
//
//   // setup
//   halstead_metric_setup(&m);
//   operators = hashmap_new();
//   operands = hashmap_new();
//
//   // parse program operators and operands
//   for (i = 0; i < t->size; i++) {
//     n = t->chromosome[i];
//     ns = node_string(n);
//
//     if (TERM_NODE(n->type)) {
//       m.nb_total_operands++;
//       if (hashmap_get(operands, ns) == NULL) {
//         hashmap_set(operands, ns, (void *) "1");
//         m.nb_unique_operands++;
//       }
//
//     } else if (FUNC_NODE(n->type)) {
//       m.nb_total_operators++;
//       if (hashmap_get(operators, ns) == NULL) {
//         hashmap_set(operators, ns, (void *) "1");
//         m.nb_unique_operators++;
//       }
//     }
//
//     free(ns);
//   }
//
//   // calculate halstead metric
//   halstead_metric_calculate(&m);
//
//   // clean up
//   hashmap_destroy(operators);
//   hashmap_destroy(operands);
//
//   return m.effort;
// }
//
// static struct node *eval_func(struct data *d, struct node *n) {
//   int i;
//   double result;
//   struct node *feval;
//
//   // setup
//   feval = node_new();
//   node_setup_feval(feval, d->rows);
//
//   // evaluate
//   switch (n->fval) {
//   case ADD:
//     for (i = 0; i < d->rows; i++) {
//       feval->data[i] = d->f_in[0][i] + d->f_in[1][i];
//     }
//     break;
//   case SUB:
//     for (i = 0; i < d->rows; i++) {
//       feval->data[i] = d->f_in[0][i] - d->f_in[1][i];
//     }
//     break;
//   case MUL:
//     for (i = 0; i < d->rows; i++) {
//       feval->data[i] = d->f_in[0][i] * d->f_in[1][i];
//     }
//     break;
//   case DIV:
//     for (i = 0; i < d->rows; i++) {
//       if (fltcmp(d->f_in[1][i], 0.0) == 0) {
//         goto eval_error;
//       }
//       feval->data[i] = d->f_in[0][i] / d->f_in[1][i];
//     }
//     break;
//   case POW:
//     for (i = 0; i < d->rows; i++) {
//       result = pow(d->f_in[0][i], d->f_in[1][i]);
//       if (isfinite(result)) {
//         feval->data[i] = result;
//       } else {
//         goto eval_error;
//       }
//     }
//     break;
//   case EXP:
//     for (i = 0; i < d->rows; i++) {
//       result = exp(d->f_in[0][i]);
//       if (isfinite(result)) {
//         feval->data[i] = result;
//       } else {
//         goto eval_error;
//       }
//     }
//     break;
//   case LOG:
//     for (i = 0; i < d->rows; i++) {
//       result = log(d->f_in[0][i]);
//       if (isfinite(result)) {
//         feval->data[i] = result;
//       } else {
//         goto eval_error;
//       }
//     }
//     break;
//   case RAD:
//     for (i = 0; i < d->rows; i++) {
//       feval->data[i] = d->f_in[0][i] * (double) (M_PI / 180.0);
//     }
//     break;
//   case SIN:
//     for (i = 0; i < d->rows; i++) {
//       feval->data[i] = sin(d->f_in[0][i]);
//     }
//     break;
//   case COS:
//     for (i = 0; i < d->rows; i++) {
//       feval->data[i] = cos(d->f_in[0][i]);
//     }
//     break;
//   default:
//     log_err("invalid function %d\n", n->type);
//     exit(-1);
//   }
//
//   feval->nth_child = n->nth_child;  // keep track nth-child of node
//   return feval;
//
// eval_error:
//   node_destroy(feval);
//   return NULL;
// }
//
// static void eval_stack_destroy_traverse(struct stack_node *n) {
//   struct node *tree_node;
//
//   if (n->next) {
//     eval_stack_destroy_traverse(n->next);
//   }
//
//   tree_node = (struct node *) n->value;
//   if (tree_node->type == FEVAL) {
//     node_destroy(tree_node);
//   }
//   free(n);
//   n = NULL;
// }
//
// static void eval_stack_destroy(struct stack *s) {
//   if (s->root) {
//     eval_stack_destroy_traverse(s->root);
//   }
//   free(s);
//   s = NULL;
// }
//
// struct node *tree_evaluate_data(struct tree *t, struct data *d) {
//   int i;
//   struct stack *s;
//   struct node *n;
//   struct node *left;
//   struct node *right;
//   struct node *feval;
//
//   // setup
//   s = stack_new();
//   left = NULL;
//   right = NULL;
//
//   // evaluate tree
//   for (i = 0; i < t->size; i++) {
//     n = t->chromosome[i];
//
//     // terminal
//     if (n->type == CONST || n->type == INPUT) {
//       stack_push(s, t->chromosome[i]);
//
//       // unary function
//     } else if (n->type == UFUNC) {
//       left = (struct node *) stack_pop(s);
//       tree_prep_data(left, d);
//       if (left->type == FEVAL) {
//         node_destroy(left);
//       }
//
//       feval = eval_func(d, n);
//       silent_check(feval);
//       stack_push(s, feval);
//
//       // binary function
//     } else if (n->type == BFUNC) {
//       right = (struct node *) stack_pop(s);
//       left = (struct node *) stack_pop(s);
//
//       tree_prep_data(left, d);
//       tree_prep_data(right, d);
//
//       if (left->type == FEVAL) {
//         node_destroy(left);
//       }
//       if (right->type == FEVAL) {
//         node_destroy(right);
//       }
//
//       feval = eval_func(d, n);
//       silent_check(feval);
//       stack_push(s, feval);
//     }
//   }
//
//   // result
//   n = (struct node *) stack_pop(s);
//
//   // clean up
//   free(s);
//   return n;
//
// error:
//   eval_stack_destroy(s);  // destroy feval nodes in stack
//   return NULL;
// }
//
// int tree_evaluate(struct tree *t, struct data *d, char *predict) {
//   struct node *output;
//
//   // pre-check
//   if (t->size < 3) {
//     t->error = -FLT_MAX;
//     t->score = -FLT_MAX;
//     t->hits = 0;
//     return -1;
//   }
//
//   // setup
//   output = tree_evaluate_data(t, d);
//   if (output == NULL) {
//     t->error = -FLT_MAX;
//     t->score = -FLT_MAX;
//     t->hits = 0;
//     return -2;
//   }
//
//   // caclulate error
//   t->hits = 0;
//   t->error = mse(d, predict, output->data);
//
//   // calculate score
//   t->score = -t->error - 0.1 * tree_halstead_metric(t);
//   // t->score = -t->error - t->size;
//
//   // clean up
//   node_destroy(output);
//
//   return 0;
// }
//
// static void tree_print_traverse(struct tree *t, struct node *n) {
//   int i;
//
//   if (TERM_NODE(n->type)) {
//     node_print(n);
//     printf(" ");
//
//   } else {
//     for (i = 0; i < n->arity; i++) {
//       tree_print_traverse(t, n->children[i]);
//     }
//     node_print(n);
//     printf(" ");
//   }
// }
//
// void tree_print(struct tree *t) {
//   tree_print_traverse(t, t->root);
//   printf("score: %.2f", t->score);
//   printf("\n");
// }
//
// static void tree_print_equation_function(struct node *n) {
//   switch (n->fval) {
//   case ADD:
//     printf(" + ");
//     break;
//   case SUB:
//     printf(" - ");
//     break;
//   case MUL:
//     printf(" * ");
//     break;
//   case DIV:
//     printf(" / ");
//     break;
//   case POW:
//     printf("**");
//     break;
//   case LOG:
//     printf("log");
//     break;
//   case EXP:
//     printf("exp");
//     break;
//   case RAD:
//     printf("rad");
//     break;
//   case SIN:
//     printf("sin");
//     break;
//   case COS:
//     printf("cos");
//     break;
//   }
// }
//
// static void tree_print_equation_traverse(struct tree *t, struct node *n) {
//   if (TERM_NODE(n->type)) {
//     if (n->type == CONST) {
//       printf("%.2f", n->nval);
//
//     } else if (n->type == INPUT) {
//       printf("%s", n->input);
//     }
//
//   } else if (n->type == UFUNC) {
//     printf("(");
//     tree_print_equation_function(n);
//     printf("(");
//     tree_print_equation_traverse(t, n->children[0]);
//     printf(")");
//     printf(")");
//
//   } else if (n->type == BFUNC) {
//     printf("(");
//     tree_print_equation_traverse(t, n->children[0]);
//     tree_print_equation_function(n);
//     tree_print_equation_traverse(t, n->children[1]);
//     printf(")");
//   }
// }
//
// void tree_print_equation(struct tree *t) {
//   tree_print_equation_traverse(t, t->root);
//   printf("\n");
// }
//
// void tree_print_chromosome(struct tree *t) {
//   int i;
//
//   for (i = 0; i < t->size; i++) {
//     node_print(t->chromosome[i]);
//     printf(" ");
//   }
//   printf("\n");
// }
//
// static char *tree_node_string(struct node *n) {
//   char buffer[30];
//
//   // setup
//   memset(buffer, '\0', sizeof(char) * 30);
//
//   // build tree node string
//   switch (n->type) {
//   case CONST:
//     snprintf(buffer, sizeof(buffer), "%.2f", n->nval);
//     break;
//   case INPUT:
//     snprintf(buffer, sizeof(buffer), "%s", n->input);
//     break;
//   case BFUNC:
//     switch (n->fval) {
//     case ADD:
//       snprintf(buffer, sizeof(buffer), "ADD");
//       break;
//     case SUB:
//       snprintf(buffer, sizeof(buffer), "SUB");
//       break;
//     case MUL:
//       snprintf(buffer, sizeof(buffer), "MUL");
//       break;
//     case DIV:
//       snprintf(buffer, sizeof(buffer), "DIV");
//       break;
//     case POW:
//       snprintf(buffer, sizeof(buffer), "POW");
//       break;
//     }
//   case UFUNC:
//     switch (n->fval) {
//     case LOG:
//       snprintf(buffer, sizeof(buffer), "LOG");
//       break;
//     case EXP:
//       snprintf(buffer, sizeof(buffer), "EXP");
//       break;
//     case RAD:
//       snprintf(buffer, sizeof(buffer), "RAD");
//       break;
//     case SIN:
//       snprintf(buffer, sizeof(buffer), "SIN");
//       break;
//     case COS:
//       snprintf(buffer, sizeof(buffer), "COS");
//       break;
//     }
//   }
//
//   return malloc_string(buffer);
// }
//
// char *tree_string(struct tree *t) {
//   int i;
//   char buffer[4096];
//   char *n;
//
//   // setup
//   tree_update(t);
//   memset(buffer, '\0', sizeof(char) * 4096);
//
//   for (i = 0; i < t->size; i++) {
//     n = tree_node_string(t->chromosome[i]);
//     snprintf(buffer + strlen(buffer), sizeof(buffer), "%s ", n);
//     free(n);
//   }
//
//   return malloc_string(buffer);
// }
//
// static char *tree_node_function_string(struct node *n) {
//   char buffer[30];
//
//   // setup
//   memset(buffer, '\0', sizeof(char) * 30);
//
//   // build tree node string
//   switch (n->type) {
//   case CONST:
//     snprintf(buffer, sizeof(buffer), "%.2f", n->nval);
//     break;
//   case INPUT:
//     snprintf(buffer, sizeof(buffer), "%s", n->input);
//     break;
//   case BFUNC:
//     switch (n->fval) {
//     case ADD:
//       snprintf(buffer, sizeof(buffer), " + ");
//       break;
//     case SUB:
//       snprintf(buffer, sizeof(buffer), " - ");
//       break;
//     case MUL:
//       snprintf(buffer, sizeof(buffer), " * ");
//       break;
//     case DIV:
//       snprintf(buffer, sizeof(buffer), " / ");
//       break;
//     case POW:
//       snprintf(buffer, sizeof(buffer), "**");
//       break;
//     }
//   case UFUNC:
//     switch (n->fval) {
//     case LOG:
//       snprintf(buffer, sizeof(buffer), "log");
//       break;
//     case EXP:
//       snprintf(buffer, sizeof(buffer), "exp");
//       break;
//     case RAD:
//       snprintf(buffer, sizeof(buffer), "rad");
//       break;
//     case SIN:
//       snprintf(buffer, sizeof(buffer), "sin");
//       break;
//     case COS:
//       snprintf(buffer, sizeof(buffer), "cos");
//       break;
//     }
//   }
//
//   return malloc_string(buffer);
// }
//
// static void tree_equation_string_traverse(struct tree *t,
//                                           struct node *n,
//                                           char *eq) {
//   char *nstr;
//
//   if (TERM_NODE(n->type)) {
//     if (n->type == CONST) {
//       snprintf(eq + strlen(eq), sizeof(eq), "%.2f", n->nval);
//     } else if (n->type == INPUT) {
//       snprintf(eq + strlen(eq), sizeof(eq), "%s", n->input);
//     }
//
//   } else if (n->type == UFUNC) {
//     // unary function
//     snprintf(eq + strlen(eq), sizeof(eq), "(");
//     nstr = tree_node_function_string(n);
//     snprintf(eq + strlen(eq), sizeof(eq), "%s", nstr);
//     free(nstr);
//
//     // child
//     snprintf(eq + strlen(eq), sizeof(eq), "(");
//     tree_equation_string_traverse(t, n->children[0], eq);
//     snprintf(eq + strlen(eq), sizeof(eq), ")");
//     snprintf(eq + strlen(eq), sizeof(eq), ")");
//
//   } else if (n->type == BFUNC) {
//     // left child
//     snprintf(eq + strlen(eq), sizeof(eq), "(");
//     tree_equation_string_traverse(t, n->children[0], eq);
//
//     // binary function
//     nstr = tree_node_function_string(n);
//     snprintf(eq + strlen(eq), sizeof(eq), "%s", nstr);
//     free(nstr);
//
//     // right child
//     tree_equation_string_traverse(t, n->children[1], eq);
//     snprintf(eq + strlen(eq), sizeof(eq), ")");
//   }
// }
//
// char *tree_equation_string(struct tree *t) {
//   char buffer[4096];
//
//   // setup
//   tree_update(t);
//   memset(buffer, '\0', sizeof(char) * 4096);
//
//   // create equation string
//   tree_equation_string_traverse(t, t->root, buffer);
//
//   return malloc_string(buffer);
// }
//
// int tree_record(struct tree *t, const char *path) {
//   FILE *fp;
//   char *eq;
//   char *rpn;
//
//   // setup
//   fp = fopen(path, "w");
//
//   // record tree stack
//   eq = tree_equation_string(t);
//   fprintf(fp, "equation: %s\n", eq);
//
//   rpn = tree_string(t);
//   fprintf(fp, "rpn: %s\n", rpn);
//
//   // record tree score and error
//   fprintf(fp, "score: %f\n", t->score);
//   fprintf(fp, "error: %f\n", t->error);
//   fprintf(fp, "\n");
//
//   // clean up
//   free(eq);
//   free(rpn);
//   fclose(fp);
//
//   return 0;
// }
//
// int tree_record_output(struct tree *t, const char *path, struct data *d) {
//   int i;
//   FILE *fp;
//   struct node *output;
//
//   // setup
//   fp = fopen(path, "w");
//
//   // evaluate tree
//   output = tree_evaluate_data(t, d);
//   if (output == NULL || output->type != FEVAL) {
//     return -1;
//   }
//
//   // record output
//   for (i = 0; i < d->rows; i++) {
//     fprintf(fp, "%f\n", output->data[i]);
//   }
//
//   // clean up
//   node_destroy(output);
//   fclose(fp);
//
//   return 0;
// }
//
// static int func_type(char *str) {
//   int i;
//   const char *ufuncs[5];
//   const char *bfuncs[5];
//
//   // setup
//   ufuncs[0] = "LOG";
//   ufuncs[1] = "EXP";
//   ufuncs[2] = "RAD";
//   ufuncs[3] = "SIN";
//   ufuncs[4] = "COS";
//
//   bfuncs[0] = "ADD";
//   bfuncs[1] = "SUB";
//   bfuncs[2] = "MUL";
//   bfuncs[3] = "DIV";
//   bfuncs[4] = "POW";
//
//   for (i = 0; i < 5; i++) {
//     if (strcmp(ufuncs[i], str) == 0) {
//       return UFUNC;
//     } else if (strcmp(bfuncs[i], str) == 0) {
//       return BFUNC;
//     }
//   }
//
//   return -1;
// }
//
// static void tree_load_const(struct node *n, char *nstr, struct stack *s) {
//   float constant;
//
//   constant = atof(nstr);
//   node_setup_const(n, constant);
//   stack_push(s, n);
// }
//
// static void tree_load_input(struct node *n, char *nstr, struct stack *s) {
//   node_setup_input(n, nstr);
//   stack_push(s, n);
// }
//
// static void tree_load_ufunc(struct node *n, char *nstr, struct stack *s) {
//   struct node *child;
//
//   if (strcmp(nstr, "LOG") == 0) {
//     node_setup_ufunc(n, LOG);
//   } else if (strcmp(nstr, "EXP") == 0) {
//     node_setup_ufunc(n, EXP);
//   } else if (strcmp(nstr, "RAD") == 0) {
//     node_setup_ufunc(n, RAD);
//   } else if (strcmp(nstr, "SIN") == 0) {
//     node_setup_ufunc(n, SIN);
//   } else if (strcmp(nstr, "COS") == 0) {
//     node_setup_ufunc(n, COS);
//   } else {
//     log_err("invalid function [%s]!", nstr);
//   }
//
//   // add children to unary function
//   child = (struct node *) stack_pop(s);
//   n->children[0] = child;
//
//   // record parent to children
//   child->parent = n;
//   child->nth_child = 0;
//
//   // push node to stack
//   stack_push(s, n);
// }
//
// static void tree_load_bfunc(struct node *n, char *nstr, struct stack *s) {
//   struct node *left;
//   struct node *right;
//
//   // setup node
//   if (strcmp(nstr, "ADD") == 0) {
//     node_setup_bfunc(n, ADD);
//   } else if (strcmp(nstr, "SUB") == 0) {
//     node_setup_bfunc(n, SUB);
//   } else if (strcmp(nstr, "MUL") == 0) {
//     node_setup_bfunc(n, MUL);
//   } else if (strcmp(nstr, "DIV") == 0) {
//     node_setup_bfunc(n, DIV);
//   } else if (strcmp(nstr, "POW") == 0) {
//     node_setup_bfunc(n, POW);
//   } else {
//     log_err("invalid function [%s]!", nstr);
//   }
//
//   // add children to binary function
//   right = (struct node *) stack_pop(s);
//   left = (struct node *) stack_pop(s);
//
//   n->children[0] = left;
//   n->children[1] = right;
//
//   // record parent to children
//   left->parent = n;
//   left->nth_child = 0;
//
//   right->parent = n;
//   right->nth_child = 1;
//
//   // push node to stack
//   stack_push(s, n);
// }
//
// static void tree_load_func(struct node *n, char *nstr, struct stack *s) {
//   int ftype;
//
//   ftype = func_type(nstr);
//   if (ftype == UFUNC) {
//     tree_load_ufunc(n, nstr, s);
//   } else if (ftype == BFUNC) {
//     tree_load_bfunc(n, nstr, s);
//   }
// }
//
// int tree_load(struct tree *t, char **rpn, int size) {
//   int i;
//   char *nstr;
//   struct node *n;
//   struct stack *s;
//
//   // setup
//   s = stack_new();
//
//   // load
//   for (i = 0; i < size; i++) {
//     nstr = rpn[i];
//     n = node_new();
//
//     // load constant node
//     if (isdigit(nstr[0])) {
//       tree_load_const(n, nstr, s);
//
//       // load input node
//     } else if (islower(nstr[0])) {
//       tree_load_input(n, nstr, s);
//
//       // load function node
//     } else {
//       tree_load_func(n, nstr, s);
//     }
//   }
//   n = (struct node *) stack_pop(s);
//   t->root = n;
//   tree_update(t);
//
//   tree_print_equation(t);
//
//   // clean up
//   stack_destroy(s);
//
//   return 0;
// }
//
// int tree_load_file(struct tree *t, const char *path) {
//   int i;
//   FILE *f;
//   char buf[4096];
//   char key[100];
//   char value[4096];
//   char **rpn;
//   int size;
//
//   // setup
//   f = fopen(path, "r");
//   memset(buf, '\0', sizeof(char) * 4096);
//   memset(key, '\0', sizeof(char) * 100);
//   memset(value, '\0', sizeof(char) * 4096);
//
//   // load file line by line
//   while (fgets(buf, sizeof(buf), f)) {
//     sscanf(buf, "%s", key);
//
//     if (strcmp(key, "rpn:") == 0) {
//       strcpy(value, buf + strlen(key) + 1);
//       rpn = split(value, " ", &size);
//       tree_load(t, rpn, size);
//     }
//
//     memset(buf, '\0', sizeof(char) * 4096);
//     memset(key, '\0', sizeof(char) * 100);
//   }
//
//   // clean up
//   for (i = 0; i < size; i++) {
//     free(rpn[i]);
//   }
//   free(rpn);
//   fclose(f);
//
//   return 0;
// }
//
// static int tree_simplify_check_children(struct node *n) {
//   int i;
//
//   for (i = 0; i < n->arity; i++) {
//     if (n->children[i]->type != CONST) {
//       return -1;
//     }
//   }
//
//   return 0;
// }
//
// static void tree_simplify_ufunc(struct node *n) {
//   int fval;
//   double nval;
//   double result;
//
//   // setup
//   fval = n->fval;
//   nval = n->children[0]->nval;
//
//   // simplify
//   switch (fval) {
//   case LOG:
//     result = log(nval);
//     break;
//   case EXP:
//     result = exp(nval);
//     break;
//   case RAD:
//     result = nval * (double) (M_PI / 180.0);
//     break;
//   case SIN:
//     result = sin(nval);
//     break;
//   case COS:
//     result = cos(nval);
//     break;
//   }
//
//   // transform from function to constant node
//   n->fval = UINITI;
//   n->arity = UINITI;
//   node_destroy(n->children[0]);
//   free(n->children);
//   n->children = NULL;
//
//   n->type = CONST;
//   n->nval = result;
// }
//
// static void tree_simplify_bfunc(struct node *n) {
//   int fval;
//   double nval1;
//   double nval2;
//   double result;
//
//   // setup
//   fval = n->fval;
//   nval1 = n->children[0]->nval;
//   nval2 = n->children[1]->nval;
//
//   // simplify
//   switch (fval) {
//   case ADD:
//     result = nval1 + nval2;
//     break;
//   case SUB:
//     result = nval1 - nval2;
//     break;
//   case MUL:
//     result = nval1 * nval2;
//     break;
//   case DIV:
//     result = nval1 * nval2;
//     break;
//   case POW:
//     result = pow(nval1, nval2);
//     break;
//   }
//
//   // transform from function to constant node
//   n->fval = UINITI;
//   n->arity = UINITI;
//   node_destroy(n->children[0]);
//   node_destroy(n->children[1]);
//   free(n->children);
//   n->children = NULL;
//
//   n->type = CONST;
//   n->nval = result;
// }
//
// static void tree_simplify_traverse(struct node *n) {
//   if (n->type == UFUNC) {
//     tree_simplify_traverse(n->children[0]);
//     if (tree_simplify_check_children(n) == 0) {
//       tree_simplify_ufunc(n);
//     }
//
//   } else if (n->type == BFUNC) {
//     tree_simplify_traverse(n->children[0]);
//     tree_simplify_traverse(n->children[1]);
//     if (tree_simplify_check_children(n) == 0) {
//       tree_simplify_bfunc(n);
//     }
//   }
// }
//
// void tree_simplify(struct tree *t) {
//   tree_simplify_traverse(t->root);
//   tree_update(t);
// }
//
//
// // CROSSOVER FUNCTIONS
// void crossover_config_defaults(struct crossover_config *cc) {
//   cc->crossover_function = point_crossover;
//   cc->probability = 0.6;
// }
//
// int point_crossover(struct tree *t1,
//                     struct tree *t2,
//                     struct crossover_config *config) {
//   int i1;
//   int i2;
//   struct node *n1;
//   struct node *n2;
//
//   // pre-check
//   if (randf(0.0, 1.0) > config->probability) {
//     return 0;
//   }
//
//   // setup
//   i1 = randi(0, t1->size - 1);
//   i2 = randi(0, t2->size - 1);
//   n1 = t1->chromosome[i1];
//   n2 = t2->chromosome[i2];
//
//   // crossover
//   if (n1 == t1->root) {
//     t1->root = n2;
//   } else {
//     n1->parent->children[n1->nth_child] = n2;
//   }
//
//   if (n2 == t2->root) {
//     t2->root = n1;
//   } else {
//     n2->parent->children[n2->nth_child] = n1;
//   }
//
//   // update
//   t1->root->parent = NULL;
//   t2->root->parent = NULL;
//   tree_update(t1);
//   tree_update(t2);
//
//   return 0;
// }
//
//
// // MUTATION FUNCTIONS
// void mutation_config_defaults(struct mutation_config *mc) {
//   mc->mutation_function = subtree_mutation;
//   mc->probability = 0.02;
//
//   mc->subtree_build_method = FULL_METHOD;
//   mc->subtree_max_depth = 2;
// }
//
// static void mutate_node(struct tree *t, struct node *n) {
//   struct node *new_node;
//
//   // generate new node
//   if (n->type == CONST) {
//     new_node = node_random_const(t->ts);
//     n->nval = new_node->nval;
//
//   } else if (n->type == INPUT) {
//     new_node = node_random_input(t->ts);
//     free(n->input);
//     n->input = new_node->input;
//
//   } else if (n->type == UFUNC) {
//     new_node = node_random_ufunc(t->fs);
//     n->fval = new_node->fval;
//     free(new_node->children);
//
//   } else if (n->type == BFUNC) {
//     new_node = node_random_bfunc(t->fs);
//     n->fval = new_node->fval;
//     free(new_node->children);
//   }
//
//   free(new_node);
// }
//
// int point_mutation(struct tree *t, struct mutation_config *config) {
//   int i;
//
//   // mutate
//   for (i = 0; i < t->size; i++) {
//     if (config->probability > randf(0, 1.0)) {
//       mutate_node(t, t->chromosome[i]);
//     }
//   }
//
//   return 0;
// }
//
// int subtree_mutation(struct tree *t, struct mutation_config *config) {
//   int i;
//   struct node *n;
//   struct tree *tmp;
//   struct tree_config tc;
//
//   // pre-check
//   if (randf(0.0, 1.0) > config->probability) {
//     return 0;
//   }
//
//   // setup
//   tc.build_method = config->subtree_build_method;
//   tc.max_depth = config->subtree_max_depth;
//   tc.fs = t->fs;
//   tc.ts = t->ts;
//   tmp = tree_new();
//   tree_generate(tmp, &tc);
//
//   // mutate
//   i = randi(0, t->size - 1);
//   n = t->chromosome[i];
//   if (n == t->root) {
//     t->root = tmp->root;
//   } else {
//     n->parent->children[n->nth_child] = tmp->root;
//   }
//   tree_update(t);
//
//   // clean up
//   node_clear_destroy(n);
//   free(tmp->chromosome);
//   free(tmp);
//
//   return 0;
// }
//
//
// // POPULATION FUNCTIONS
// struct population *population_new(int size) {
//   int i;
//   struct population *p;
//
//   // pre-check
//   check(size > 0, E_NUM_OF_INDIVIDUALS);
//
//   // setup
//   p = (struct population *) malloc(sizeof(struct population));
//   p->individuals = (struct tree **) malloc(sizeof(struct tree *) * size);
//   for (i = 0; i < size; i++) {
//     p->individuals[i] = NULL;
//   }
//   p->size = size;
//
//   return p;
// error:
//   return NULL;
// }
//
// void population_destroy(void *target) {
//   int i;
//   struct population *p;
//   void *t;
//
//   p = (struct population *) target;
//   for (i = 0; i < p->size; i++) {
//     t = p->individuals[i];
//     if (t != NULL) {
//       tree_destroy(t);
//     }
//   }
//   free(p->individuals);
//   free(p);
//   p = NULL;
// }
//
// struct population *population_generate(struct tree_config *tc, int size) {
//   int i;
//   struct population *p;
//   struct tree *t;
//
//   // setup
//   p = population_new(size);
//
//   // generate population
//   for (i = 0; i < size; i++) {
//     t = tree_new();
//     tree_generate(t, tc);
//     p->individuals[i] = t;
//   }
//
//   return p;
// }
//
// struct tree *population_best(struct population *p) {
//   int i;
//   int best_index;
//   struct tree *best;
//   struct tree *contender;
//   struct tree *result;
//
//   // pre-check
//   check(p->individuals != NULL, E_POPULATION);
//   check(p->size > 0, E_POPULATION_EMPTY);
//
//   // find best
//   best_index = randi(0, p->size - 1);
//   best = p->individuals[best_index];
//
//   for (i = 0; i < p->size; i++) {
//     contender = p->individuals[i];
//
//     if (fltcmp(contender->score, best->score) == 1) {
//       best = contender;
//     }
//   }
//
//   // set population best
//   result = tree_new();
//   tree_copy(best, result);
//
//   return result;
// error:
//   return NULL;
// }
//
// void population_clear(struct population *p) {
//   int i;
//   struct tree *t;
//
//   for (i = 0; i < p->size; i++) {
//     t = p->individuals[i];
//     if (t) {
//       node_clear_destroy(t->root);
//       t->root = NULL;
//     }
//   }
// }
//
// void population_copy(struct population *src, struct population *dest) {
//   int i;
//
//   for (i = 0; i < src->size; i++) {
//     tree_copy(src->individuals[i], dest->individuals[i]);
//   }
// }
//
// void population_print(struct population *p) {
//   int i;
//
//   for (i = 0; i < p->size; i++) {
//     tree_print(p->individuals[i]);
//   }
// }
//
//
// // SELECTION FUNCTIONS
// void selection_config_defaults(struct selection_config *sc) {
//   sc->selection_function = &tournament_selection;
//   sc->tournament_size = 10;
// }
//
// int tournament_selection(struct population *p,
//                          struct population *selected,
//                          struct selection_config *sc) {
//   int i;
//   int j;
//   int index;
//   struct tree *best;
//   struct tree *contender;
//
//   // pre-check
//   check(p != NULL, E_POPULATION);
//   check(selected != NULL, E_SELECTED);
//   check(sc != NULL, E_SELECTION_CONFIG);
//   check(sc->tournament_size > 0, E_TOURNAMENT_SIZE);
//
//   // setup
//   population_clear(selected);
//
//   // select selected
//   for (j = 0; j < p->size; j++) {
//     index = randi(0, p->size - 1);
//     best = p->individuals[index];
//
//     // select best in tournament
//     for (i = 0; i < sc->tournament_size; i++) {
//       index = randi(0, p->size - 1);
//       contender = p->individuals[index];
//
//       if (contender->score > best->score) {
//         best = contender;
//       }
//     }
//
//     // copy best to selected
//     best->hits = 0;
//     best->score = 0.0;
//     best->error = 0.0;
//     tree_destroy(selected->individuals[j]);
//     selected->individuals[j] = tree_new();
//     tree_copy(best, selected->individuals[j]);
//   }
//   selected->size = p->size;
//
//   return 0;
// error:
//   return -1;
// }


}  // end of gp namespace
}  // end of yarl namespace
