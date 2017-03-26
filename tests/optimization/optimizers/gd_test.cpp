#include <functional>

#include <gtest/gtest.h>

#include "yarl/optimization/benchmark.hpp"
#include "yarl/optimization/optimizers/gdopt.hpp"

namespace yarl {

TEST(gdopt, setup) {
  struct gdopt opt;

  gdopt_setup(&opt);
  ASSERT_EQ(opt.configured, false);
  ASSERT_EQ(opt.max_iter, 1000);
}

TEST(gdopt, configure) {
  int max_iter;
  VecX eta(2);
  VecX x(2);
  gdopt opt;

  // setup
  max_iter = 1000;
  eta << 1.0, 1.0;
  x << 0.0, 0.0;

  // clang-format off
  gdopt_configure(
    &opt,
    max_iter,
    eta,
    x,
    std::bind(beale, std::placeholders::_1)
  );
  // clang-format on

  ASSERT_EQ(true, opt.configured);
  ASSERT_EQ(max_iter, opt.max_iter);
  ASSERT_FLOAT_EQ(eta(0), opt.eta(0));
  ASSERT_FLOAT_EQ(eta(1), opt.eta(1));
  ASSERT_FLOAT_EQ(x(0), opt.x(0));
  ASSERT_FLOAT_EQ(x(1), opt.x(1));
}

TEST(gdopt, calculate_gradient) {
  int max_iter;
  VecX eta(2);
  VecX x(2);
  VecX df(2, 1);
  gdopt opt;

  // setup
  max_iter = 1000;
  eta << 1.0, 1.0;
  x << 0.0, 0.0;

  // clang-format off
  gdopt_configure(
    &opt,
    max_iter,
    eta,
    x,
    std::bind(beale, std::placeholders::_1)
  );
  // clang-format on
  gdopt_calculate_gradient(&opt, df);

  ASSERT_FLOAT_EQ(-12.75, df(0));
  ASSERT_FLOAT_EQ(0.0, df(1));
}

TEST(gdopt, optimize) {
  int max_iter;
  VecX eta(2);
  VecX x(2);
  gdopt opt;

  // setup
  max_iter = 10000;
  eta << 0.006, 0.006;
  x << 0.0, 0.0;

  // clang-format off
  gdopt_configure(
    &opt,
    max_iter,
    eta,
    x,
    std::bind(beale, std::placeholders::_1)
  );
  // clang-format on
  gdopt_optimize(&opt);

  ASSERT_TRUE(opt.x(0) > 2.7);
  ASSERT_TRUE(opt.x(0) <= 3.0);
  ASSERT_TRUE(opt.x(1) > 0.4);
  ASSERT_TRUE(opt.x(1) <= 0.5);
}

}  // end of yarl namespace
