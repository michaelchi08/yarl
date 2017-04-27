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
  std::string data_file;
  double train, test, valid;
  parser.addParam("/config/dataset/data", &data_file);
  parser.addParam("/config/dataset/train", &train);
  parser.addParam("/config/dataset/test", &test);
  parser.addParam("/config/dataset/valid", &valid);

  // selection operator configs
  parser.addParam("/config/selection/tournament_size",
                  &this->selection_config.tournament_size);

  // crossover operator configs
  parser.addParam("/config/crossover/probability",
                  &this->crossover_config.probability);

  // mutation operator configs
  parser.addParam("/config/mutation/probability",
                  &this->mutation_config.probability);
  parser.addParam("/config/mutation/build_method",
                  &this->mutation_config.build_method);
  parser.addParam("/config/mutation/max_depth",
                  &this->mutation_config.max_depth);

  // tree configs
  int tree_method, tree_depth;
  parser.addParam("/config/tree_config/method", &tree_method);
  parser.addParam("/config/tree_config/depth", &tree_depth);

  // parse configurations
  retval = parser.load(config_file);
  if (retval != 0) {
    return -1;
  }

  // setup tree config
  retval = this->tree_config.configure(tree_method, tree_depth);
  if (retval != 0) {
    log_error("Failed to configure tree config!");
    return -4;
  }

  // setup population
  retval = this->population.configure(nb_individuals, &this->tree_config);
  if (retval != 0) {
    log_error("Failed to configure population!");
    return -2;
  }

  // setup dataset
  std::string dir = basedir(config_file);
  std::string data_path;
  paths_combine(dir, data_file, data_path);
  retval = this->dataset.load(data_path, train, test, valid);
  this->dataset.predict = "x";
  if (retval != 0) {
    log_error("Failed to load dataset!");
    return -3;
  }

  // finish up
  this->configured = true;
  return 0;
}

int GPOpt::iterate() {
  Population selection;

  // evaluate population
  this->population.evaluate(this->dataset.train_data, this->dataset.predict);

  // apply genetic operators
  tournament_selection(
    this->selection_config.tournament_size, this->population, selection);
  for (size_t i = 0; i < selection.individuals.size(); i += 2) {
    Tree *t1 = selection.individuals[i];
    Tree *t2 = selection.individuals[i + 1];

    t1->update();
    t2->update();

    point_crossover(this->crossover_config.probability, *t1, *t2);
    subtree_mutation(this->mutation_config.probability,
                     this->mutation_config.build_method,
                     this->mutation_config.max_depth,
                     *t1);
    subtree_mutation(this->mutation_config.probability,
                     this->mutation_config.build_method,
                     this->mutation_config.max_depth,
                     *t2);
  }

  // copy selected population over
  this->population.copyFrom(selection);

  return 0;
}

int GPOpt::solve() {
  Tree best;

  for (int i = 0; i < this->max_generations; i++) {
    this->iterate();
    this->population.best(best);

    std::cout << "gen: " << i << "\t";
    std::cout << "tree: " << best.toString() << "\t";
    std::cout << "score: " << best.score << "\n";
  }

  return 0;
}

void GPOpt::printBest() {
  Tree best;

  this->population.best(best);
  std::cout << "tree: " << best.toString() << std::endl;
  std::cout << "score: " << best.score << std::endl;
  std::cout << std::endl;
}

}  // end of gp namespace
}  // end of yarl namespace
