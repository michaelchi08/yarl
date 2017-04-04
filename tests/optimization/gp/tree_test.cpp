#include "yarl/test.hpp"
#include "yarl/optimization/gp/tree.hpp"

#define TEST_SINE_DATA "./tests/data/sine.csv"
#define TEST_CIRCLE_DATA "./tests/data/circle.csv"
#define TEST_ELLIPTIC_DATA "./tests/data/elliptic.csv"
#define TEST_IMPLICIT_DATA "./tests/data/implicit.csv"

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

  tree.configure(&tc);
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

  tc.configure(FULL_METHOD, 2);
  t.configure(&tc);
  t.generate();
  t.printStack();
}

TEST(Tree, prepData) {
  Tree t;
  TreeConfig tc;

  tc.configure(FULL_METHOD, 2);
  t.configure(&tc);
}

TEST(Tree, toString) {
  Tree t;
  TreeConfig tc;

  tc.configure(FULL_METHOD, 2);
  t.configure(&tc);
  t.generate();
  t.toString();
}

TEST(Tree, printEquation) {
  Tree t;
  TreeConfig tc;

  tc.configure(FULL_METHOD, 2);
  t.configure(&tc);
  t.generate();
  t.printEquation();
}

// int test_tree_prep_data(void)
// {
//     struct node n;
//     struct dataset *d;
//     double data[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//
//     #<{(| setup |)}>#
//     d = dataset_new(TEST_SINE_DATA, 1, ",", "x");
//     node_setup(&n);
//
//     #<{(| test load input |)}>#
//     n.type = INPUT;
//     n.input = malloc_string("x");
//     n.nth_child = 0;
//     tree_prep_data(&n, d->data);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][0], 0.0) == 0);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][1], 1.0) == 0);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][2], 2.0) == 0);
//
//     #<{(| test load constant |)}>#
//     n.type = CONST;
//     n.nval = 123.0;
//     n.nth_child = 1;
//     tree_prep_data(&n, d->data);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][0], 123.0) == 0);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][1], 123.0) == 0);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][2], 123.0) == 0);
//
//     #<{(| test load function eval |)}>#
//     n.type = FEVAL;
//     n.nth_child = 1;
//     n.data = data;
//     tree_prep_data(&n, d->data);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][0], 10.0) == 0);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][1], 9.0) == 0);
//     mu_check(fltcmp(d->data->f_in[n.nth_child][2], 8.0) == 0);
//
//     #<{(| clean up |)}>#
//     free(n.input);
//     dataset_destroy(d);
//
//     return 0;
// }
//
// int test_tree_halstead_metric(void)
// {
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//
//     #<{(| test and assert |)}>#
//     tree_halstead_metric(t);
//
//     #<{(| clean up |)}>#
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_evaluate_data(void)
// {
//     int i;
//     struct tree *t;
//     struct node *n;
//     struct dataset *d;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//     d = dataset_new(TEST_SINE_DATA, 1, ",", "y");
//
//     #<{(| evaluate data |)}>#
//     n = tree_evaluate_data(t, d->data);
//     for (i = 0; i < d->data->rows; i++) {
//         printf("row[%d]: %f\n", i, n->data[i]);
//     }
//
//     #<{(| clean up |)}>#
//     node_destroy(n);
//     dataset_destroy(d);
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_evaluate(void)
// {
//     struct tree *t;
//     struct dataset *d;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//     d = dataset_new(TEST_SINE_DATA, 1, ",", "y");
//
//     #<{(| evaluate data |)}>#
//     tree_evaluate(t, d->data, d->predict);
//     mu_print("error: %f\n", t->error);
//     mu_print("hits: %d\n", t->hits);
//     mu_check(fltcmp(t->error, 0.0) == 0);
//
//     #<{(| clean up |)}>#
//     dataset_destroy(d);
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_string(void)
// {
//     struct tree *t;
//     char *tstr;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//
//     #<{(| evaluate data |)}>#
//     tstr = tree_string(t);
//     mu_print("tree->rpn: %s\n", tstr);
//     mu_check(strcmp(tstr, "100.00 RAD x MUL SIN ") == 0);
//
//     #<{(| clean up |)}>#
//     free(tstr);
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_print_equation(void)
// {
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//
//     #<{(| print equation |)}>#
//     tree_print_equation(t);
//
//     #<{(| clean up |)}>#
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_equation_string(void)
// {
//     char *tstr;
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//
//     #<{(| create equation string |)}>#
//     tstr = tree_equation_string(t);
//     mu_print("%s\n", tstr);
//
//     #<{(| clean up |)}>#
//     free(tstr);
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_record(void)
// {
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//
//     #<{(| record tree |)}>#
//     tree_record(t, "/tmp/tree.model");
//
//     #<{(| clean up |)}>#
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_record_output(void)
// {
//     struct tree *t;
//     struct dataset *d;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//     d = dataset_new(TEST_SINE_DATA, 1, ",", "y");
//
//     #<{(| record tree output |)}>#
//     tree_record_output(t, "/tmp/tree.output", d->data);
//
//     #<{(| clean up |)}>#
//     dataset_destroy(d);
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_tree_load(void)
// {
//     int i;
//     char **rpn;
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     rpn = malloc(sizeof(char *) * 5);
//     rpn[0] = malloc_string("2");
//     rpn[1] = malloc_string("3");
//     rpn[2] = malloc_string("SUB");
//     rpn[3] = malloc_string("3");
//     rpn[4] = malloc_string("ADD");
//
//     #<{(| test tree load |)}>#
//     t = tree_new();
//     tree_load(t, rpn, 5);
//
//     #<{(| clean up |)}>#
//     for (i = 0; i < 5; i++) {
//         free(rpn[i]);
//     }
//     free(rpn);
//     tree_destroy(t);
//
//     return 0;
// }
//
// int test_tree_load_file(void)
// {
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//     tree_record(t, "/tmp/tree.model");
//     destroy_sine_tree(t);
//
//     #<{(| load file |)}>#
//     t = tree_new();
//     tree_load_file(t, "/tmp/tree.model");
//     tree_print(t);
//
//     #<{(| clean up |)}>#
//     tree_destroy(t);
//
//     return 0;
// }
//
// int test_tree_simplify(void)
// {
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     t = setup_sine_tree();
//
//     #<{(| simplify |)}>#
//     tree_simplify(t);
//     tree_print(t);
//     tree_print_equation(t);
//
//     #<{(| clean up |)}>#
//     destroy_sine_tree(t);
//
//     return 0;
// }
//
// int test_crossover_config_defaults(void)
// {
//     struct crossover_config cc;
//
//     crossover_config_defaults(&cc);
//     mu_check(cc.crossover_function == point_crossover);
//     mu_check(fltcmp(cc.probability, 0.6) == 0);
//
//     return 0;
// }
//
// int test_point_crossover(void)
// {
//     struct tree t1;
//     struct tree t2;
//     struct tree_config tc;
//     struct crossover_config cc;
//     char inputs[MAX_INPUTS][MAX_INPUT_VAR_SIZE];
//
//     #<{(| setup |)}>#
//     strcpy(inputs[0], "x");
//     strcpy(inputs[1], "y");
//
//     tc.build_method = FULL_METHOD;
//     tc.max_depth = 2;
//     tc.fs = function_set_defaults();
//     tc.ts = terminal_set_defaults(inputs, 2);
//
//     tree_generate(&t1, &tc);
//     tree_generate(&t2, &tc);
//
//     cc.probability = 1.0;
//
//     #<{(| point crossover |)}>#
//     tree_print_chromosome(&t1);
//     tree_print_chromosome(&t2);
//     point_crossover(&t1, &t2, &cc);
//     tree_print_chromosome(&t1);
//     tree_print_chromosome(&t2);
//
//     #<{(| clean up |)}>#
//     function_set_destroy(tc.fs);
//     terminal_set_destroy(tc.ts);
//     node_clear_destroy(t1.root);
//     node_clear_destroy(t2.root);
//     free(t1.chromosome);
//     free(t2.chromosome);
//
//     return 0;
// }
//
// int test_mutation_config_defaults(void)
// {
//     struct mutation_config mc;
//
//     mutation_config_defaults(&mc);
//
//     mu_check(mc.mutation_function == subtree_mutation);
//     mu_check(fltcmp(mc.probability, 0.02) == 0);
//     mu_check(mc.subtree_build_method == FULL_METHOD);
//     mu_check(mc.subtree_max_depth == 2);
//
//     return 0;
// }
//
// int test_point_mutation(void)
// {
//     struct tree t;
//     struct tree_config tc;
//     struct mutation_config mc;
//     char inputs[MAX_INPUTS][MAX_INPUT_VAR_SIZE];
//
//     #<{(| setup |)}>#
//     strcpy(inputs[0], "x");
//     strcpy(inputs[1], "y");
//
//     tc.build_method = FULL_METHOD;
//     tc.max_depth = 2;
//     tc.fs = function_set_defaults();
//     tc.ts = terminal_set_defaults(inputs, 2);
//
//     tree_generate(&t, &tc);
//
//     mc.probability = 1.0;
//
//     #<{(| point mutation |)}>#
//     tree_print_chromosome(&t);
//     point_mutation(&t, &mc);
//     tree_print_chromosome(&t);
//
//     #<{(| clean up |)}>#
//     function_set_destroy(tc.fs);
//     terminal_set_destroy(tc.ts);
//     node_clear_destroy(t.root);
//     free(t.chromosome);
//
//     return 0;
// }
//
// int test_subtree_mutation(void)
// {
//     struct tree t;
//     struct tree_config tc;
//     struct mutation_config mc;
//     char inputs[MAX_INPUTS][MAX_INPUT_VAR_SIZE];
//
//     #<{(| setup |)}>#
//     strcpy(inputs[0], "x");
//     strcpy(inputs[1], "y");
//
//     tc.build_method = FULL_METHOD;
//     tc.max_depth = 2;
//     tc.fs = function_set_defaults();
//     tc.ts = terminal_set_defaults(inputs, 2);
//
//     tree_generate(&t, &tc);
//
//     #<{(| subtree mutation |)}>#
//     mc.probability = 1.0;
//     mc.subtree_build_method = FULL_METHOD;
//     mc.subtree_max_depth = 2;
//
//     tree_print_chromosome(&t);
//     subtree_mutation(&t, &mc);
//     tree_print_chromosome(&t);
//
//     #<{(| clean up |)}>#
//     function_set_destroy(tc.fs);
//     terminal_set_destroy(tc.ts);
//     node_clear_destroy(t.root);
//     free(t.chromosome);
//
//     return 0;
// }
//
// int test_population_new_and_destroy(void)
// {
//     int i;
//     struct population *p;
//
//     #<{(| setup |)}>#
//     p = population_new(100);
//
//     #<{(| test |)}>#
//     mu_check(p->individuals != NULL);
//     mu_check(p->size == 100);
//     for (i = 0; i < 100; i++) {
//         mu_check(p->individuals[i] == NULL);
//     }
//
//     #<{(| clean up |)}>#
//     population_destroy(p);
//
//     return 0;
// }
//
// int test_population_generate(void)
// {
//     int i;
//     struct population *p;
//     struct tree_config tc;
//     char inputs[MAX_INPUTS][MAX_INPUT_VAR_SIZE];
//
//     #<{(| setup |)}>#
//     strcpy(inputs[0], "x");
//     strcpy(inputs[1], "y");
//
//     tc.build_method = FULL_METHOD;
//     tc.max_depth = 2;
//     tc.fs = function_set_defaults();
//     tc.ts = terminal_set_defaults(inputs, 2);
//
//     #<{(| test |)}>#
//     p = population_generate(&tc, 10);
//     for (i = 0; i < 10; i++) {
//         tree_print(p->individuals[i]);
//     }
//
//     #<{(| clean up |)}>#
//     function_set_destroy(tc.fs);
//     terminal_set_destroy(tc.ts);
//     population_destroy(p);
//
//     return 0;
// }
//
// int test_population_best(void)
// {
//     int i;
//     struct population *p;
//     struct tree *t;
//
//     #<{(| setup |)}>#
//     p = population_new(10);
//
//     #<{(| test |)}>#
//     for (i = 0; i < 10; i++) {
//         t = tree_new();
//         t->score = i;
//         p->individuals[i] = t;
//     }
//     t = population_best(p);
//     printf("best score: %f\n", t->score);
//
//     #<{(| clean up |)}>#
//     tree_destroy(t);
//     population_destroy(p);
//
//     return 0;
// }
//
// int test_population_clear(void)
// {
//     int i;
//     struct population *p;
//     struct tree_config tc;
//     struct tree *t;
//     char inputs[MAX_INPUTS][MAX_INPUT_VAR_SIZE];
//
//     #<{(| setup |)}>#
//     strcpy(inputs[0], "x");
//     strcpy(inputs[1], "y");
//
//     tc.build_method = FULL_METHOD;
//     tc.max_depth = 2;
//     tc.fs = function_set_defaults();
//     tc.ts = terminal_set_defaults(inputs, 2);
//
//     p = population_generate(&tc, 10);
//
//     #<{(| test |)}>#
//     population_clear(p);
//     for (i = 0; i < 10; i++) {
//         t = p->individuals[i];
//         mu_check(t->root == NULL);
//     }
//
//     #<{(| clean up |)}>#
//     population_destroy(p);
//     function_set_destroy(tc.fs);
//     terminal_set_destroy(tc.ts);
//
//     return 0;
// }
//
// int test_selection_config_defaults(void)
// {
//     struct selection_config sc;
//
//     selection_config_defaults(&sc);
//     mu_check(sc.selection_function == tournament_selection);
//     mu_check(sc.tournament_size == 10);
//
//     return 0;
// }
//
// int test_tournament_selection(void)
// {
//     int i;
//     struct selection_config sc;
//     struct population *p;
//     struct population *selected;
//     struct tree_config tc;
//     char inputs[MAX_INPUTS][MAX_INPUT_VAR_SIZE];
//
//     #<{(| setup |)}>#
//     strcpy(inputs[0], "x");
//     strcpy(inputs[1], "y");
//
//     tc.build_method = FULL_METHOD;
//     tc.max_depth = 2;
//     tc.fs = function_set_defaults();
//     tc.ts = terminal_set_defaults(inputs, 2);
//
//     p = population_generate(&tc, 10);
//     selected = population_new(10);
//     sc.tournament_size = 2;
//
//     #<{(| test |)}>#
//     for (i = 0; i < p->size; i++) {
//         p->individuals[i]->score = i;
//     }
//     printf("old population:\n");
//     population_print(p);
//
//     tournament_selection(p, selected, &sc);
//
//     printf("\nselected population:\n");
//     population_print(selected);
//
//     #<{(| clean up |)}>#
//     population_destroy(p);
//     population_destroy(selected);
//     function_set_destroy(tc.fs);
//     terminal_set_destroy(tc.ts);
//
//     return 0;
// }

}  // end of gp namespace
}  // end of yarl namespace
