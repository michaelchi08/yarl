#include "yarl/test.hpp"
#include "yarl/optimization/gp/mutation.hpp"


namespace yarl {
namespace gp {

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

}  // end of gp namespace
}  // end of yarl namespace
