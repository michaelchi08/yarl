#include "yarl/optimization/gp/gpmetric.hpp"


// double mse(struct data *desired, char *predict, double *predicted) {
//   int i;
//   double e;
//   double error;
//   int predict_index;
//
//   #<{(| setup |)}>#
//   error = 0.0;
//   predict_index = data_field_index(desired, predict);
//
//   #<{(| calculate mean squared error |)}>#
//   for (i = 0; i < desired->rows; i++) {
//     e = fabs(desired->data[predict_index][i] - predicted[i]);
//     error += e;
//   }
//
//   #<{(| check error |)}>#
//   if (isfinite(error)) {
//     error = pow(error, 2) / (double) desired->rows;
//   } else {
//     error = FLT_MAX;
//   }
//
//   return error;
// }
//
// double sse(struct data *desired, char *predict, double *predicted) {
//   int i;
//   double e;
//   double error;
//   int predict_index;
//
//   #<{(| setup |)}>#
//   error = 0.0;
//   predict_index = data_field_index(desired, predict);
//
//   #<{(| calculate mean squared error |)}>#
//   for (i = 0; i < desired->rows; i++) {
//     e = fabs(desired->data[predict_index][i] - predicted[i]);
//     error += e;
//   }
//
//   #<{(| check error |)}>#
//   if (isfinite(error)) {
//     error = pow(error, 2);
//   } else {
//     error = FLT_MAX;
//   }
//
//   return error;
// }
//
// void halstead_metric_setup(struct halstead_metric *m) {
//   m->nb_unique_operators = 0;
//   m->nb_unique_operands = 0;
//   m->nb_total_operators = 0;
//   m->nb_total_operands = 0;
//
//   m->vocab = 0;
//   m->length = 0;
//   m->volume = 0.0;
//   m->difficulty = 0.0;
//   m->effort = 0.0;
// }
//
// int halstead_metric_calculate(struct halstead_metric *m) {
//   float n1, n2;
//   float N1, N2;
//
//   n1 = m->nb_unique_operators;
//   n2 = m->nb_unique_operands;
//
//   N1 = m->nb_total_operators;
//   N2 = m->nb_total_operands;
//
//   m->vocab = n1 + n2;
//   m->length = N1 + N2;
//   m->volume = m->length * log(m->vocab);
//   m->difficulty = n1 / 2.0 * N2 / n2;
//   m->effort = m->difficulty * m->volume;
//
//   return 0;
// }
//
// void halstead_metric_print(struct halstead_metric *m) {
//   printf("nb_unique_operators: %d\n", m->nb_unique_operators);
//   printf("nb_unique_operands: %d\n", m->nb_unique_operands);
//
//   printf("nb_total_operators: %d\n", m->nb_total_operators);
//   printf("nb_total_operands: %d\n", m->nb_total_operands);
//
//   printf("vocab: %d\n", m->vocab);
//   printf("length: %d\n", m->length);
//   printf("volume: %f\n", m->volume);
//   printf("difficulty: %f\n", m->difficulty);
//   printf("effort: %f\n", m->effort);
// }
