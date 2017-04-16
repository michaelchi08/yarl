#include "yarl/optimization/gp/metric.hpp"

namespace yarl {
namespace gp {

double mse(const Data &desired,
           const std::string &predict,
           const VecX &predicted) {
  double error_sum, mse;
  int predict_index;

  // setup
  error_sum = 0.0;
  predict_index = desired.fieldIndex(predict);

  // calculate mean squared error
  for (int i = 0; i < desired.rows; i++) {
    error_sum += fabs(desired.data(i, predict_index) - predicted(i));
  }

  // check error
  if (std::isfinite(error_sum)) {
    mse = pow(error_sum, 2) / (double) desired.rows;
  } else {
    mse = FLT_MAX;
  }

  return mse;
}

double sse(const Data &desired,
           const std::string &predict,
           const VecX &predicted) {
  double error_sum, sse;
  int predict_index;

  // setup
  error_sum = 0.0;
  predict_index = desired.fieldIndex(predict);

  // calculate mean squared error
  for (int i = 0; i < desired.rows; i++) {
    error_sum += fabs(desired.data(i, predict_index) - predicted(i));
  }

  // check error
  if (std::isfinite(error_sum)) {
    sse = pow(error_sum, 2);
  } else {
    sse = FLT_MAX;
  }

  return sse;
}


int HalsteadMetric::calculate() {
  float n1, n2;
  float N1, N2;

  n1 = this->nb_unique_operators;
  n2 = this->nb_unique_operands;

  N1 = this->nb_total_operators;
  N2 = this->nb_total_operands;

  this->vocab = n1 + n2;
  this->length = N1 + N2;
  this->volume = this->length * log(this->vocab);
  this->difficulty = n1 / 2.0 * N2 / n2;
  this->effort = this->difficulty * this->volume;

  return 0;
}

void HalsteadMetric::print() {
  std::cout << "Unique operators: " << this->nb_unique_operators << std::endl;
  std::cout << "Unique operands: " << this->nb_unique_operands << std::endl;

  std::cout << "Total operators: " << this->nb_total_operators << std::endl;
  std::cout << "Total operands: " << this->nb_total_operands << std::endl;

  std::cout << "Vocab: " << this->vocab << std::endl;
  std::cout << "Length: " << this->length << std::endl;
  std::cout << "Volume: " << this->volume << std::endl;
  std::cout << "Difficulty: " << this->difficulty << std::endl;
  std::cout << "Effort: " << this->effort << std::endl;
}

}  // end of gp namespace
}  // end of yarl namespace
