#include "yarl/test.hpp"
#include "yarl/optimization/gp/gpopt.hpp"

#define TEST_CONFIG "tests/data/optimization/gp/config.xml"

namespace yarl {
namespace gp {

TEST(GPOpt, constructor) {
  GPOpt opt;

  EXPECT_FALSE(opt.configured);
  EXPECT_EQ(100, opt.max_generations);
  EXPECT_DOUBLE_EQ(0.0, opt.target_score);
  EXPECT_EQ(0, opt.generation);
}

TEST(GPOpt, configure) {
  int retval;
  GPOpt opt;

  retval = opt.configure(TEST_CONFIG);

  EXPECT_EQ(0, retval);
  EXPECT_EQ(5, opt.max_generations);
  EXPECT_DOUBLE_EQ(0.0, opt.target_score);
}

TEST(GPOpt, iterate) {
  int retval;
  GPOpt opt;

  retval = opt.configure(TEST_CONFIG);
  opt.iterate();

  EXPECT_EQ(0, retval);
}

TEST(GPOpt, solve) {
  int retval;
  GPOpt opt;

  retval = opt.configure(TEST_CONFIG);
  opt.solve();

  EXPECT_EQ(0, retval);
}

}  // end of gp namespace
}  // end of yarl namespace
