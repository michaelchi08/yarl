#include "yarl/test.hpp"
#include "yarl/optimization/gp/selection.hpp"


namespace yarl {
namespace gp {

// int test_selection_config_defaults()
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
// int test_tournament_selection()
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
