#ifndef YARL_OPTIMIZATION_GP_DATA_HPP
#define YARL_OPTIMIZATION_GP_DATA_HPP

#include <vector>
#include <string>
#include <iostream>

#include "yarl/utils/utils.hpp"

namespace yarl {
namespace gp {

class Data {
public:
  bool loaded;

  std::vector<std::string> fields;
  int rows;
  int cols;
  MatX data;

  Data(void);
  int load(MatX data, std::vector<std::string> &fields);
  int load(std::string data_file);
  int fieldIndex(std::string field);
};

class Dataset {
  Data train_data;
  Data valid_data;
  Data test_data;
  std::string predict;

  Dataset(void);
  int load(Data data, float train, float validation, float test);
};

}  // end of gp namespace
}  // end of yarl namespace
#endif
