#include "yarl/optimization/gp/gpopt.hpp"

namespace yarl {
namespace gp {

int GPOpt::configure(const std::string &config_file) {
  ConfigParser parser;
  int retval;

  // general configs
  int nb_individuals;
  parser.addParam("/config/max_generations", &this->max_generations);
  parser.addParam("/config/target_score", &this->target_score);
  parser.addParam("/config/nb_individuals", &nb_individuals);

  // dataset configs
  std::string data_path;
  double train, test, valid;
  parser.addParam("/config/dataset/data", &data_path);
  parser.addParam("/config/dataset/train", &train);
  parser.addParam("/config/dataset/test", &test);
  parser.addParam("/config/dataset/valid", &valid);

  // tree configs
  int tree_method, tree_depth;
  parser.addParam("/config/tree_config/method", &tree_method);
  parser.addParam("/config/tree_config/depth", &tree_depth);

  // parse configurations
  retval = parser.load(config_file);
  if (retval != 0) {
    return -1;
  }

  // setup population
  retval = this->population.configure(
    nb_individuals, &this->tree_config, &this->data);
  if (retval != 0) {
    log_err("Failed to configure population!");
    return -2;
  }

  // setup dataset
  std::string dir = basedir(config_file);
  retval = this->dataset.load(dir + "/" + data_path, train, test, valid);
  if (retval != 0) {
    log_err("Failed to load dataset!");
    return -3;
  }

  // setup tree config
  retval = this->tree_config.configure(tree_method, tree_depth);
  if (retval != 0) {
    log_err("Failed to configure tree config!");
    return -4;
  }

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
