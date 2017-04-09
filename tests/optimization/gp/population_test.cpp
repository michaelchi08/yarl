#include "yarl/test.hpp"
#include "yarl/optimization/gp/population.hpp"


namespace yarl {
namespace gp {

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

}  // end of gp namespace
}  // end of yarl namespace
