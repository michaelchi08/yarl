#include "yarl/optimization/gp/data.hpp"

namespace yarl {
namespace gp {

int Data::load(const MatX &data, const std::vector<std::string> &fields) {
  // pre-eheck
  if (this->loaded) {
    this->fields.clear();
  }

  // load data
  this->loaded = true;
  this->rows = data.rows();
  this->cols = data.cols();
  this->data = data;
  this->fields = fields;

  return 0;
}

int Data::load(const std::string &data_file) {
  // pre-eheck
  if (this->loaded) {
    this->fields.clear();
  }

  // load fields
  if (csvheader(data_file, this->fields) != 0) {
    return -1;
  }

  // load data
  if (csv2mat(data_file, true, this->data) != 0) {
    return -1;
  }
  this->rows = this->data.rows();
  this->cols = this->data.cols();

  return 0;
}

int Data::fieldIndex(const std::string &field) const {
  auto it = std::find(this->fields.begin(), this->fields.end(), field);
  if (it == this->fields.end()) {
    return -1;
  } else {
    return std::distance(this->fields.begin(), it);
  }
  return 0;
}


int Dataset::load(const Data &d, float train, float valid, float test) {
  double train_rows, valid_rows, test_rows;
  MatX train_mat, valid_mat, test_mat;

  // pre-check
  if (fltcmp((train + valid + test), 1.0) != 0) {
    log_err("train + valid + test != 1.0");
    return -1;
  }

  // partition train, valid and test set
  train_rows = d.rows * train;
  valid_rows = d.rows * valid;
  test_rows = d.rows * test;

  train_mat = d.data.block(0, 0, train_rows, d.cols);
  valid_mat = d.data.block(train_rows, 0, valid_rows, d.cols);
  test_mat = d.data.block(train_rows + valid_rows, 0, test_rows, d.cols);

  this->train_data.load(train_mat, d.fields);
  this->valid_data.load(valid_mat, d.fields);
  this->test_data.load(test_mat, d.fields);

  return 0;
}

int Dataset::load(const std::string &data_file,
                  float train,
                  float valid,
                  float test) {
  Data data;

  if (data.load(data_file) != 0) {
    return -2;
  }

  return this->load(data, train, valid, test);
}

}  // end of gp namespace
}  // end of yarl namespace
