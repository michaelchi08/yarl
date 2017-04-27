#include "yarl/test.hpp"
#include "yarl/optimization/gp/selection.hpp"


namespace yarl {
namespace gp {

TEST(Selection, tournament_selection) {
  Population population, selected;
  TreeConfig tree_config;

  tree_config.configure(GROW_METHOD, 2);
  population.configure(10, &tree_config);
  population.individuals[0]->score = -10.0;
  population.individuals[1]->score = -10.0;
  population.individuals[2]->score = -10.0;
  population.individuals[3]->score = -10.0;
  population.individuals[4]->score = -10.0;
  population.individuals[5]->score = -10.0;
  population.individuals[6]->score = -10.0;
  population.individuals[7]->score = -10.0;
  population.individuals[8]->score = -10.0;
  population.individuals[9]->score = 0.0;
  std::cout << "best: " << population.individuals[9]->toString() << std::endl;

  tournament_selection(10, population, selected);
  population.print();
  std::cout << std::endl;
  selected.print();
}


}  // end of gp namespace
}  // end of yarl namespace
