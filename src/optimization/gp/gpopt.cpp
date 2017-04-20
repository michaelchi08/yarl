#include "yarl/optimization/gp/gpopt.hpp"

namespace yarl {
namespace gp {

int GPOpt::configure(const std::string &config_file) {
  ConfigParser parser;

  // parse configuration file
  parser.addParam("/config/max_generations", &this->max_generations);
  parser.addParam("/config/target_score", &this->target_score);
  int retval = parser.load(config_file);
  if (retval != 0) {
    return -1;
  }

  // setup
  // this->tree_config.configure(GROW_METHOD, 2);
  // this->population.configure(10, &this->tree_config, &this->data);

  // finish up
  this->configured = true;
  return 0;
}

int GPOpt::iterate() {
  return 0;
}

int GPOpt::solve() {
  return 0;
}

}  // end of gp namespace
}  // end of yarl namespace
