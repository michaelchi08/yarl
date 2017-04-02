#ifndef YARL_OPTIMIZATION_OPTIMIZERS_GPDATA_HPP
#define YARL_OPTIMIZATION_OPTIMIZERS_GPDATA_HPP

#include <vector>
#include <string>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {

class GPData {
public:
  bool loaded;

  std::vector<std::string> fields;
  int rows;
  int cols;
  MatX data;

  VecX data_in;
  VecX data_out;

  GPData(void);
  int load(MatX data, std::vector<std::string> &fields);
  int load(std::string data_file);
  int fieldIndex(std::string field);
};

class GPDataset {
  GPData train_data;
  GPData valid_data;
  GPData test_data;
  std::string predict;

  GPDataset(void);
  int load(GPData data, float train, float validation, float test);
};

}  // end of yarl namespace
#endif
