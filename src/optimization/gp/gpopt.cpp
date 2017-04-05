#include "yarl/optimization/gp/gpopt.hpp"

// struct config *sr_setup(int nb_populations,
//                         int nb_individuals,
//                         struct tree_config *tc) {
//   int i;
//   struct config *c;
//
//   // setup
//   c = (struct config *) malloc(sizeof(struct config));
//
//   // details
//   c->nb_populations = nb_populations;
//   c->nb_individuals = nb_individuals;
//
//   // population
//   c->p = (struct population **) malloc(sizeof(struct population *) *
//                                        nb_populations);
//   c->selected = (struct population **) malloc(sizeof(struct population *) *
//                                               nb_populations);
//   for (i = 0; i < nb_populations; i++) {
//     c->p[i] = population_generate(tc, nb_individuals);
//     c->selected[i] = population_new(nb_individuals);
//   }
//
//   // genetic operators
//   selection_config_defaults(&c->selection);
//   crossover_config_defaults(&c->crossover);
//   mutation_config_defaults(&c->mutation);
//
//   // termination criteria
//   c->max_generations = 500;
//   c->target_score = 0.0;
//
//   return c;
// }
//
// void sr_destroy(void *target) {
//   int i;
//   struct config *c;
//
//   c = (struct config *) target;
//   for (i = 0; i < c->nb_populations; i++) {
//     population_destroy(c->p[i]);
//     population_destroy(c->selected[i]);
//   }
//   free(c->p);
//   free(c->selected);
//
//   free(c);
// }
//
// int sr_reproduce(struct config *c) {
//   int i;
//   int j;
//   int retval;
//   struct tree *t1;
//   struct tree *t2;
//   struct population *p;
//   struct population *selected;
//
//   // pre-check
//   check(c->selection.selection_function, ESFUNC);
//   check(c->crossover.crossover_function, ECFUNC);
//   check(c->mutation.mutation_function, EMFUNC);
//
//   for (i = 0; i < c->nb_populations; i++) {
//     p = c->p[i];
//     selected = c->selected[i];
//
//     // selection
//     population_clear(selected);
//     retval = c->selection.selection_function(p, selected, &c->selection);
//     if (retval != 0) {
//       log_err(ESELFAIL);
//     }
//
//     // crossover and mutation
//     population_clear(p);
//     for (j = 0; j < selected->size; j += 2) {
//       t1 = selected->individuals[j];
//       t2 = selected->individuals[j + 1];
//
//       c->crossover.crossover_function(t1, t2, &c->crossover);
//       c->mutation.mutation_function(t1, &c->mutation);
//       c->mutation.mutation_function(t2, &c->mutation);
//
//       tree_copy(t1, p->individuals[j]);
//       tree_copy(t2, p->individuals[j + 1]);
//     }
//   }
//
//   return 0;
// error:
//   return -1;
// }
//
// void sr_evaluate(struct config *c, struct data *d, char *predict) {
//   int i;
//   int j;
//   struct tree *t;
//
// #ifdef OPENMP_SUPPORT
// #pragma omp parallel for
//   for (i = 0; i < c->nb_populations; i++) {
// #pragma omp parallel for
//     for (j = 0; j < c->p[i]->size; j++) {
//       t = c->p[i]->individuals[j];
//
//       if (t->size < 100) {
//         tree_evaluate(t, d, predict);
//         tree_simplify(t);
//       } else {
//         t->score = -FLT_MAX;
//       }
//     }
//   }
// #else
//   for (i = 0; i < c->nb_populations; i++) {
//     for (j = 0; j < c->p[i]->size; j++) {
//       t = c->p[i]->individuals[j];
//
//       if (t->size < 100) {
//         tree_evaluate(t, d, predict);
//         tree_simplify(t);
//       } else {
//         t->score = -FLT_MAX;
//       }
//     }
//   }
// #endif
// }
//
// void sr_exchange_best(struct config *c) {
//   int i;
//   int j;
//   struct population *best;
//
//   // pre-check
//   if (c->nb_populations < 2) {
//     return;
//   }
//
//   // setup
//   best = population_new(c->nb_populations);
//
//   // obtain best in each population
//   for (i = 0; i < c->nb_populations; i++) {
//     best->individuals[i] = population_best(c->p[i]);
//   }
//
//   // exchange best across populations
//   for (i = 0; i < c->nb_populations; i++) {
//     for (j = 0; j < c->nb_populations; j++) {
//       if (i != j) {
//         tree_copy(best->individuals[i], c->p[j]->individuals[0]);
//       }
//     }
//   }
//
//   // clean up
//   population_destroy(best);
// }
//
// struct tree *sr_best(struct config *c) {
//   int i;
//   struct tree *the_one;
//   struct population *best;
//
//   // setup
//   best = population_new(c->nb_populations);
//
//   // obtain best of all populations
//   for (i = 0; i < c->nb_populations; i++) {
//     best->individuals[i] = population_best(c->p[i]);
//   }
//   the_one = population_best(best);
//
//   // clean up
//   population_destroy(best);
//
//   return the_one;
// }
//
// void sr_print_best(struct config *c, struct dataset *d, int generation) {
//   struct tree *best;
//
//   printf("generation: %d\t", generation);
//
//   best = sr_best(c);
//   tree_evaluate(best, d->train, d->predict);
//   printf("train_error: %.2f\t", best->error);
//
//   tree_evaluate(best, d->validation, d->predict);
//   printf("valid_error: %.2f\t", best->error);
//
//   tree_evaluate(best, d->test, d->predict);
//   printf("test_error: %.2f\n", best->error);
//   tree_print_equation(best);
//   printf("\n");
//
//   tree_destroy(best);
// }
//
// int sr_record_best(struct config *c, struct dataset *d) {
//   int data_index;
//   struct tree *best;
//
//   // setup
//   best = sr_best(c);
//   data_index = data_field_index(d->train, d->predict);
//
//   // record
//   tree_record(best, MODEL_FILE);
//   tree_record_output(best, MODEL_OUTPUT_FILE, d->train);
//   data_record_desired_ouput(d->train, DATA_OUTPUT_FILE, data_index);
//
//   // clean up
//   tree_destroy(best);
//
//   return 0;
// }
//
// int sr_record_generation(struct config *c, int generation) {
//   char *t;
//   struct tree *best;
//   FILE *record;
//
//   // setup
//   record = fopen(SR_FILE, "a");
//   best = sr_best(c);
//   t = tree_string(best);
//
//   // record
//   fprintf(record, "%i,", generation);
//   fprintf(record, "%s,", t);
//   fprintf(record, ",");
//   fprintf(record, "%d,", best->size);
//   fprintf(record, "%f,", best->score);
//   fprintf(record, "%f,", best->error);
//   fprintf(record, "%d", best->evaluated);
//   fprintf(record, "\n");
//
//   // clean up
//   free(t);
//   fclose(record);
//   tree_destroy(best);
//
//   return 0;
// }
//
// int sr_evolve_terminate(struct config *c) {
//   struct tree *best;
//
//   // setup
//   best = sr_best(c);
//
//   // check target score
//   if (fltcmp(best->score, 0.0) == 0) {
//     tree_print(best);
//     tree_destroy(best);
//     log_info("target score met!");
//     return 1;
//   }
//
//   // clean up
//   tree_destroy(best);
//
//   return 0;
// }
//
// void sr_print(struct config *c, int generation) {
//   char *tstr;
//   struct tree *best;
//
//   // setup
//   best = sr_best(c);
//
//   // print
//   log_info(
//     "gen: %d, score: %f, error: %.2f", generation, best->score,
//     best->error);
//   tstr = tree_string(best);
//   printf("%s\n\n", tstr);
//
//   // clean up
//   free(tstr);
//   tree_destroy(best);
// }
//
// int sr_evolve(struct config *c, struct dataset *d) {
//   int i;
//   int retval;
//   char *tstr;
//   struct tree *best;
//
//   // setup
//   sr_evaluate(c, d->train, d->predict);
//
//   // evolve
//   for (i = 0; i < c->max_generations; i++) {
//     // terminate?
//     if (sr_evolve_terminate(c) == 1) {
//       log_info("termination criteria met!");
//       break;
//     }
//
//     // reproduce
//     retval = sr_reproduce(c);
//     if (retval != 0) {
//       log_err("railed to reproduce!");
//       return -1;
//     }
//
//     // evaluate
//     if (i % 5 == 0) {
//       sr_exchange_best(c);
//     } else {
//       sr_evaluate(c, d->train, d->predict);
//     }
//     sr_evaluate(c, d->train, d->predict);
//     sr_print_best(c, d, i);
//     sr_record_best(c, d);
//     sr_record_generation(c, i);
//   }
//
//   // print best
//   log_info("max generation reached!");
//   best = sr_best(c);
//   tstr = tree_string(best);
//   printf("%s\n\n", tstr);
//   free(tstr);
//   tree_destroy(best);
//
//   return 0;
// }
