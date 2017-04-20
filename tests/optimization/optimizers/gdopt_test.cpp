#include "yarl/test.hpp"
#include "yarl/optimization/benchmark.hpp"
#include "yarl/optimization/optimizers/gdopt.hpp"

namespace yarl {

TEST(GDOpt, constructor) {
  GDOpt opt;
  EXPECT_EQ(opt.configured, false);
}

TEST(GDOpt, configure) {
  int max_iter;
  VecX eta(2);
  VecX x(2);
  GDOpt opt;

  max_iter = 1000;
  eta << 1.0, 1.0;
  x << 0.0, 0.0;

  opt.configure(max_iter, eta, x, std::bind(beale, std::placeholders::_1));

  EXPECT_EQ(true, opt.configured);
  EXPECT_EQ(max_iter, opt.max_iter);
  EXPECT_FLOAT_EQ(eta(0), opt.eta(0));
  EXPECT_FLOAT_EQ(eta(1), opt.eta(1));
  EXPECT_FLOAT_EQ(x(0), opt.x(0));
  EXPECT_FLOAT_EQ(x(1), opt.x(1));
}

TEST(GDOpt, calcGradient) {
  int max_iter;
  VecX eta(2);
  VecX x(2);
  VecX df(2, 1);
  GDOpt opt;

  max_iter = 1000;
  eta << 1.0, 1.0;
  x << 0.0, 0.0;

  opt.configure(max_iter, eta, x, std::bind(beale, std::placeholders::_1));
  opt.calcGradient(df);
  // std::cout << df << std::endl;

  EXPECT_FLOAT_EQ(-12.75, df(0));
  EXPECT_FLOAT_EQ(0.0, df(1));
}

TEST(GDOpt, optimize) {
  int max_iter;
  VecX eta(2);
  VecX x(2);
  GDOpt opt;

  max_iter = 10000;
  eta << 0.006, 0.006;
  x << 0.0, 0.0;

  opt.configure(max_iter, eta, x, std::bind(beale, std::placeholders::_1));
  opt.optimize();
  // std::cout << opt.x << std::endl;

  EXPECT_TRUE(opt.x(0) > 2.7);
  EXPECT_TRUE(opt.x(0) <= 3.0);
  EXPECT_TRUE(opt.x(1) > 0.4);
  EXPECT_TRUE(opt.x(1) <= 0.5);
}

}  // end of yarl namespace
