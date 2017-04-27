#include "yarl/optimization/gp/gpopt.hpp"

#define TEST_CONFIG "./config/config.xml"

int main(void) {
  yarl::gp::GPOpt opt;
  int retval;

  retval = opt.configure(TEST_CONFIG);
  if (retval != 0) {
    log_error("Failed to configure GPOpt!");
    return -1;
  }

  retval = opt.solve();
  if (retval != 0) {
    log_error("Failed to solve problem");
    return -2;
  }

  return 0;
}
