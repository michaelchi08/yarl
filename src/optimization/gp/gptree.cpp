#include "yarl/optimization/gp/gptree.hpp"


// // FUNCTION SET FUNCTIONS
// struct function_set *function_set_new(void) {
//   int i;
//   struct function_set *fs;
//
//   fs = (struct function_set *) malloc(sizeof(struct function_set));
//   for (i = 0; i < MAX_FUNCTIONS; i++) {
//     fs->unary_functions[i] = UINITI;
//     fs->binary_functions[i] = UINITI;
//   }
//   fs->nb_unary_functions = 0;
//   fs->nb_binary_functions = 0;
//
//   return fs;
// }
//
// void function_set_destroy(void *target) {
//   struct function_set *fs;
//
//   fs = (struct function_set *) target;
//   free(fs);
//   fs = NULL;
// }
//
// struct function_set *function_set_defaults(void) {
//   struct function_set *fs;
//
//   fs = (struct function_set *) malloc(sizeof(struct function_set));
//   function_set_setup(fs);
//
//   fs->unary_functions[0] = LOG;
//   fs->unary_functions[1] = EXP;
//   fs->unary_functions[2] = RAD;
//   fs->unary_functions[3] = SIN;
//   fs->unary_functions[4] = COS;
//   fs->nb_unary_functions = 5;
//
//   fs->binary_functions[0] = ADD;
//   fs->binary_functions[1] = SUB;
//   fs->binary_functions[2] = MUL;
//   fs->binary_functions[3] = DIV;
//   fs->binary_functions[4] = POW;
//   fs->nb_binary_functions = 5;
//
//   return fs;
// }
//
// void function_set_setup(struct function_set *fs) {
//   memset(fs->unary_functions, UINITI, sizeof(int) * MAX_FUNCTIONS);
//   fs->nb_unary_functions = 0;
//
//   memset(fs->binary_functions, UINITI, sizeof(int) * MAX_FUNCTIONS);
//   fs->nb_binary_functions = 0;
// }
//
// void function_set_clear(struct function_set *fs) {
//   function_set_setup(fs);
// }
//
//
// // TERMINAL SET FUNCTIONS
// struct terminal_set *terminal_set_new(void) {
//   int i;
//   struct terminal_set *ts;
//
//   ts = (struct terminal_set *) malloc(sizeof(struct terminal_set));
//
//   // constants
//   for (i = 0; i < MAX_CONSTANTS; i++) {
//     ts->constants[i] = UINITF;
//   }
//   ts->nb_constants = 0;
//
//   // inputs
//   for (i = 0; i < MAX_INPUTS; i++) {
//     memset(ts->inputs[i], UINITC, sizeof(char) * MAX_INPUT_VAR_SIZE);
//   }
//   ts->nb_inputs = 0;
//
//   return ts;
// }
//
// void terminal_set_destroy(void *target) {
//   struct terminal_set *ts;
//
//   ts = (struct terminal_set *) target;
//   free(ts);
//   ts = NULL;
// }
//
// struct terminal_set *terminal_set_defaults(char inputs[MAX_INPUTS]
//                                                       [MAX_INPUT_VAR_SIZE],
//                                            int nb_inputs) {
//   int i;
//   struct terminal_set *ts;
//
//   ts = (struct terminal_set *) malloc(sizeof(struct terminal_set));
//   terminal_set_setup(ts);
//   ts->constants[0] = 0.0;
//   ts->constants[1] = 1.0;
//   ts->constants[2] = 2.0;
//   ts->constants[3] = 3.0;
//   ts->constants[4] = 4.0;
//   ts->constants[5] = 5.0;
//   ts->constants[6] = 6.0;
//   ts->constants[7] = 7.0;
//   ts->constants[8] = 8.0;
//   ts->constants[9] = 9.0;
//   ts->constants[10] = 10.0;
//   ts->nb_constants = 11;
//
//   for (i = 0; i < nb_inputs; i++) {
//     memset(ts->inputs[i], '\0', sizeof(char) * MAX_INPUT_VAR_SIZE);
//     strcpy(ts->inputs[i], inputs[i]);
//   }
//   ts->nb_inputs = nb_inputs;
//
//   return ts;
// }
//
// void terminal_set_setup(struct terminal_set *ts) {
//   int i;
//
//   for (i = 0; i < MAX_CONSTANTS; i++) {
//     ts->constants[i] = UINITF;
//   }
//   ts->nb_constants = 0;
//
//   for (i = 0; i < MAX_INPUTS; i++) {
//     memset(ts->inputs[i], UINITC, sizeof(char) * MAX_INPUT_VAR_SIZE);
//   }
//   ts->nb_inputs = 0;
// }
//
// void terminal_set_clear(struct terminal_set *ts) {
//   terminal_set_setup(ts);
// }
//
//
// // NODE FUNCTIONS
// void node_setup(struct node *n) {
//   // general
//   n->type = UINITI;
//   n->parent = NULL;
//   n->nth_child = UINITI;
//
//   // constant
//   n->nval = UINITI;
//
//   // input
//   n->input = NULL;
//
//   // function
//   n->fval = UINITI;
//   n->arity = UINITI;
//   n->children = NULL;
//
//   // evaluation
//   n->data = NULL;
//   n->data_length = 0;
// }
//
// void node_setup_const(struct node *n, double constant) {
//   // general
//   n->type = CONST;
//   n->parent = NULL;
//   n->nth_child = UINITI;
//
//   // constant
//   n->nval = constant;
//
//   // input
//   n->input = NULL;
//
//   // function
//   n->fval = UINITI;
//   n->arity = UINITI;
//   n->children = NULL;
//
//   // evaluation
//   n->data = NULL;
//   n->data_length = 0;
// }
//
// void node_setup_input(struct node *n, char *input) {
//   // general
//   n->type = INPUT;
//   n->parent = NULL;
//   n->nth_child = UINITI;
//
//   // constant
//   n->nval = UINITI;
//
//   // input
//   n->input = malloc_string(input);
//
//   // function
//   n->fval = UINITI;
//   n->arity = UINITI;
//   n->children = NULL;
//
//   // evaluation
//   n->data = NULL;
//   n->data_length = 0;
// }
//
// void node_setup_ufunc(struct node *n, int function) {
//   // general
//   n->type = UFUNC;
//   n->parent = NULL;
//   n->nth_child = UINITI;
//
//   // constant
//   n->nval = UINITI;
//
//   // input
//   n->input = NULL;
//
//   // function
//   n->fval = function;
//   n->arity = 1;
//   n->children = (struct node **) malloc(sizeof(struct node *) * 1);
//
//   // evaluation
//   n->data = NULL;
//   n->data_length = 0;
// }
//
// void node_setup_bfunc(struct node *n, int function) {
//   // general
//   n->type = BFUNC;
//   n->parent = NULL;
//   n->nth_child = UINITI;
//
//   // constant
//   n->nval = UINITI;
//
//   // input
//   n->input = NULL;
//
//   // function
//   n->fval = function;
//   n->arity = 2;
//   n->children = (struct node **) malloc(sizeof(struct node *) * 2);
//
//   // evaluation
//   n->data = NULL;
//   n->data_length = 0;
// }
//
// void node_setup_feval(struct node *n, int size) {
//   // general
//   n->type = FEVAL;
//   n->parent = NULL;
//   n->nth_child = UINITI;
//
//   // constant
//   n->nval = UINITI;
//
//   // input
//   n->input = NULL;
//
//   // function
//   n->fval = UINITI;
//   n->arity = UINITI;
//   n->children = NULL;
//
//   // evaluation
//   n->data = (double *) malloc(sizeof(double) * size);
//   n->data_length = size;
// }
//
// struct node *node_new(void) {
//   struct node *n;
//
//   n = (struct node *) malloc(sizeof(struct node));
//   node_setup(n);
//
//   return n;
// }
//
// void node_destroy(void *target) {
//   int i;
//   struct node *n;
//
//   n = (struct node *) target;
//   if (n->input) {
//     free(n->input);
//   }
//
//   if (n->data) {
//     free(n->data);
//   }
//
//   if (n->children) {
//     for (i = 0; i < n->arity; i++) {
//       node_destroy(n->children[i]);
//     }
//     free(n->children);
//   }
//
//   free(n);
//   n = NULL;
// }
//
// void node_clear_destroy(void *target) {
//   int i;
//   struct node *n;
//
//   n = (struct node *) target;
//   if (target == NULL) {
//     return;
//   }
//
//   if (n->data) {
//     free(n->data);
//     n->data = NULL;
//   }
//
//   if (n->input) {
//     free(n->input);
//     n->input = NULL;
//   }
//
//   if (n->children) {
//     for (i = 0; i < n->arity; i++) {
//       node_clear_destroy(n->children[i]);
//     }
//     free(n->children);
//     n->children = NULL;
//   }
//
//   free(n);
//   n = NULL;
// }
//
// void node_copy(struct node *src, struct node *dest) {
//   int i;
//
//   // general
//   dest->type = src->type;
//   dest->parent = src->parent;
//   dest->nth_child = src->nth_child;
//
//   // constant
//   if (src->type == CONST) {
//     dest->nval = src->nval;
//   }
//
//   // input
//   if (src->type == INPUT) {
//     if (src->input) {
//       dest->input = malloc_string(src->input);
//     }
//   }
//
//   // function
//   if (src->type == UFUNC || src->type == BFUNC) {
//     dest->fval = src->fval;
//     dest->arity = src->arity;
//
//     // this function does not copy the children, if you want that
//     // use node_deepcopy() instead
//   }
//
//   // evaluation
//   if (src->type == FEVAL) {
//     if (src->data) {
//       dest->data = (double *) malloc(sizeof(double) * src->data_length);
//       for (i = 0; i < src->data_length; i++) {
//         dest->data[i] = src->data[i];
//       }
//       dest->data_length = src->data_length;
//     }
//   }
// }
//
// void node_deepcopy(struct node *src, struct node *dest) {
//   int i;
//
//   // pre-check
//   if (src == NULL) {
//     dest = NULL;
//     return;
//   }
//
//   // general
//   dest->type = src->type;
//   dest->parent = src->parent;
//   dest->nth_child = src->nth_child;
//
//   // constant
//   if (src->type == CONST) {
//     dest->nval = src->nval;
//   }
//
//   // input
//   if (src->type == INPUT) {
//     if (src->input) {
//       dest->input = malloc_string(src->input);
//     }
//   }
//
//   // function
//   if (src->type == UFUNC || src->type == BFUNC) {
//     dest->fval = src->fval;
//     dest->arity = src->arity;
//
//     if (dest->children == NULL) {
//       dest->children =
//         (struct node **) malloc(sizeof(struct node *) * src->arity);
//     }
//
//     for (i = 0; i < src->arity; i++) {
//       dest->children[i] = node_new();
//       node_deepcopy(src->children[i], dest->children[i]);
//     }
//   }
//
//   // evaluation
//   if (src->type == FEVAL) {
//     if (src->data) {
//       dest->data = (double *) malloc(sizeof(double) * src->data_length);
//       for (i = 0; i < src->data_length; i++) {
//         dest->data[i] = src->data[i];
//       }
//       dest->data_length = src->data_length;
//     }
//   }
// }
//
// int node_equals(struct node *n1, struct node *n2) {
//   int i;
//
//   // pre-check
//   if (n1 == NULL || n2 == NULL || n1->type != n2->type) {
//     return 0;
//   }
//
//   // constant
//   if (n1->type == CONST) {
//     if (fltcmp(n1->nval, n2->nval) != 0) {
//       return 0;
//     }
//   }
//
//   // input
//   if (n1->type == INPUT) {
//     if (strcmp(n1->input, n2->input) != 0) {
//       return 0;
//     }
//   }
//
//   // function
//   if (n1->type == UFUNC || n2->type == BFUNC) {
//     if (n1->fval != n2->fval) {
//       return 0;
//     } else if (n1->arity != n2->arity) {
//       return 0;
//     }
//   }
//
//   // evaluation
//   if (n1->type == FEVAL && n1->data_length == n2->data_length) {
//     for (i = 0; i < n1->data_length; i++) {
//       if (fltcmp(n1->data[i], n2->data[i]) != 0) {
//         return 0;
//       }
//     }
//   }
//
//   return 1;
// }
//
// int node_deepequals(struct node *n1, struct node *n2) {
//   int i;
//   int retval;
//
//   if (TERM_NODE(n1->type) && TERM_NODE(n2->type)) {
//     return node_equals(n1, n2);
//
//   } else if (FUNC_NODE(n1->type) && FUNC_NODE(n2->type)) {
//     if (node_equals(n1, n2) == 0) {
//       return 0;
//     }
//
//     for (i = 0; i < n1->arity; i++) {
//       retval = node_deepequals(n1->children[i], n2->children[i]);
//       if (retval == 0) {
//         return 0;
//       }
//     }
//   }
//
//   return 1;
// }
//
// char *node_string(struct node *n) {
//   char buffer[30];
//   char *node_str;
//
//   // pre-check
//   if (n == NULL) {
//     return NULL;
//   }
//
//   // build node string
//   if (n->type == CONST) {
//     sprintf(buffer, "T[%f]", n->nval);
//
//   } else if (n->type == INPUT) {
//     sprintf(buffer, "T[%s]", n->input);
//
//   } else if (n->type == UFUNC || n->type == BFUNC) {
//     sprintf(buffer, "F[%d]", n->fval);
//   }
//
//   // copy and return node string
//   node_str = (char *) malloc(sizeof(char) * strlen(buffer) + 1);
//   strcpy(node_str, buffer);
//   return node_str;
// }
//
// void node_print(struct node *n) {
//   // pre-check
//   if (n == NULL) {
//     return;
//   }
//
//   // print node
//   if (n->type == CONST) {
//     printf("T[%.2f]", n->nval);
//
//   } else if (n->type == INPUT) {
//     printf("T[%s]", n->input);
//
//   } else if (n->type == UFUNC || n->type == BFUNC) {
//     printf("F[%d]", n->fval);
//   }
// }
//
// struct node *node_random_input(struct terminal_set *ts) {
//   int i;
//   struct node *n;
//
//   i = randi(0, ts->nb_inputs - 1);
//   n = node_new();
//   n->type = INPUT;
//   n->input = malloc_string(ts->inputs[i]);
//
//   return n;
// }
//
// struct node *node_random_const(struct terminal_set *ts) {
//   int i;
//   struct node *n;
//
//   i = randi(0, ts->nb_constants - 1);
//   n = node_new();
//   n->type = CONST;
//   n->nval = ts->constants[i];
//
//   return n;
// }
//
// struct node *node_random_ufunc(struct function_set *fs) {
//   int i;
//   struct node *n;
//
//   i = randi(0, fs->nb_unary_functions - 1);
//   n = node_new();
//   n->type = UFUNC;
//   n->fval = fs->unary_functions[i];
//   n->arity = 1;
//   n->children = (struct node **) malloc(sizeof(struct node *) * n->arity);
//
//   return n;
// }
//
// struct node *node_random_bfunc(struct function_set *fs) {
//   int i;
//   struct node *n;
//
//   i = randi(0, fs->nb_binary_functions - 1);
//   n = node_new();
//   n->type = BFUNC;
//   n->fval = fs->binary_functions[i];
//   n->arity = 2;
//   n->children = (struct node **) malloc(sizeof(struct node *) * n->arity);
//
//   return n;
// }
//
// struct node *node_random_func(struct function_set *fs) {
//   // pre-check
//   if (fs->nb_unary_functions == 0) {
//     return node_random_bfunc(fs);
//   } else if (fs->nb_binary_functions == 0) {
//     return node_random_ufunc(fs);
//   }
//
//   // return random function
//   if (randf(0.0, 1.0) > 0.5) {
//     return node_random_ufunc(fs);
//   } else {
//     return node_random_bfunc(fs);
//   }
// }
//
// struct node *node_random_term(struct terminal_set *ts) {
//   // pre-check
//   if (ts->nb_inputs == 0) {
//     return node_random_const(ts);
//   } else if (ts->nb_constants == 0) {
//     return node_random_input(ts);
//   }
//
//   // return random terminal
//   if (randf(0.0, 1.0) > 0.5) {
//     return node_random_input(ts);
//   } else {
//     return node_random_const(ts);
//   }
// }
//
//
// // TREE FUNCTIONS
// void tree_setup(struct tree *t) {
//   t->root = NULL;
//   t->chromosome = NULL;
//
//   t->nb_inputs = 0;
//   t->nb_constants = 0;
//   t->nb_functions = 0;
//
//   t->size = 0;
//   t->depth = 0;
//
//   t->error = 0;
//   t->score = 0;
//   t->hits = 0;
//   t->evaluated = 0;
//
//   t->fs = NULL;
//   t->ts = NULL;
// }
//
// void tree_clear(struct tree *t) {
//   tree_setup(t);
// }
//
// struct tree *tree_new(void) {
//   struct tree *t;
//
//   t = (struct tree *) malloc(sizeof(struct tree));
//   tree_setup(t);
//
//   return t;
// }
//
// void tree_destroy(void *target) {
//   struct tree *t;
//
//   // pre-check
//   if (target == NULL) {
//     return;
//   }
//
//   // destroy
//   t = (struct tree *) target;
//   if (t->root) {
//     node_destroy(t->root);
//   }
//   if (t->chromosome) {
//     free(t->chromosome);
//     t->chromosome = NULL;
//   }
//
//   free(t);
//   t = NULL;
// }
//
// void tree_config_defaults(struct tree_config *tc,
//                           struct function_set *fs,
//                           struct terminal_set *ts) {
//   tc->build_method = FULL_METHOD;
//   tc->max_depth = 2;
//   tc->fs = fs;
//   tc->ts = ts;
// }
//
// void tree_copy(struct tree *src, struct tree *dest) {
//   if (dest->root) {
//     node_clear_destroy(dest->root);
//   }
//   dest->root = node_new();
//   node_deepcopy(src->root, dest->root);
//   tree_update(dest);
//
//   dest->nb_inputs = src->nb_inputs;
//   dest->nb_constants = src->nb_constants;
//   dest->nb_functions = src->nb_functions;
//
//   dest->size = src->size;
//   dest->depth = src->depth;
//
//   dest->error = src->error;
//   dest->score = src->score;
//   dest->hits = src->hits;
//   dest->evaluated = src->evaluated;
//
//   dest->evaluated = src->evaluated;
//
//   dest->fs = src->fs;
//   dest->ts = src->ts;
// }
//
// int tree_size(struct node *n) {
//   int i;
//   int size;
//
//   size = 1;
//
//   if (TERM_NODE(n->type)) {
//     return 1;
//   } else if (FUNC_NODE(n->type)) {
//     for (i = 0; i < n->arity; i++) {
//       size += tree_size(n->children[i]);
//     }
//   }
//
//   return size;
// }
//
// static void tree_update_traverse(struct tree *t, struct node *n, int depth)
// {
//   int i;
//
//   // pre-check
//   if (depth > t->depth) {
//     t->depth++;
//   }
//
//   // traverse
//   if (TERM_NODE(n->type)) {
//     t->chromosome[t->size] = n;
//     t->size++;
//
//   } else if (FUNC_NODE(n->type)) {
//     for (i = 0; i < n->arity; i++) {
//       n->children[i]->parent = n;
//       n->children[i]->nth_child = i;
//       tree_update_traverse(t, n->children[i], depth + 1);
//     }
//     t->chromosome[t->size] = n;
//     t->size++;
//   }
// }
//
// void tree_update(struct tree *t) {
//   int size;
//
//   // reset chromosome, size and depth
//   if (t->chromosome) {
//     free(t->chromosome);
//   }
//   size = tree_size(t->root);
//   t->chromosome = (struct node **) malloc(sizeof(struct node *) * size);
//   t->depth = 0;
//   t->size = 0;
//
//   // update tree
//   tree_update_traverse(t, t->root, 0);
//   t->chromosome[size - 1] = t->root;
// }
//
// static void tree_build(
//   int method, struct tree *t, struct node *n, int depth, int max_depth) {
//   int i;
//   struct node *child;
//
//   // pre-check
//   if (depth > t->depth) {
//     t->depth++;
//   }
//
//   // grow method
//   for (i = 0; i < n->arity; i++) {
//     if ((depth + 1) == max_depth) {
//       // create terminal node
//       child = node_random_term(t->ts);
//       child->parent = n;
//       child->nth_child = i;
//       n->children[i] = child;
//
//     } else if (method == GROW_METHOD && randf(0.0, 1.0) > 0.8) {
//       // create terminal node
//       child = node_random_term(t->ts);
//       child->parent = n;
//       child->nth_child = i;
//       n->children[i] = child;
//
//     } else {
//       // create function node
//       child = node_random_func(t->fs);
//       child->parent = n;
//       child->nth_child = i;
//       n->children[i] = child;
//
//       tree_build(method, t, child, depth + 1, max_depth);
//     }
//
//     t->size++;
//   }
// }
//
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
