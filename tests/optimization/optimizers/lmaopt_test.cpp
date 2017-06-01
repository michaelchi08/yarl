#include "yarl/test.hpp"
#include "yarl/optimization/benchmark.hpp"
#include "yarl/optimization/optimizers/lmaopt.hpp"

namespace yarl {

std::vector<MatX> generate_data() {
  VecX input;
  VecX beta;

  std::vector<double> inputs;
  std::vector<double> outputs;

  std::vector<MatX> data;

  // setup
  input.resize(2);
  beta.resize(2);

  beta(0) = 1.0;
  beta(1) = 100.0;

  // generate data
  for (double x = -3.5; x < 3.5; x += 0.1) {
    for (double y = -3.5; y < 3.5; y += 0.1) {
      input << x, y;
      inputs.push_back(input(0));
      inputs.push_back(input(1));
      outputs.push_back(rosenbrock(input, beta));
    }
  }

  // convert data to matrices and vectors
  MatX x;
  VecX y;

  y.resize(outputs.size());
  for (size_t i = 0; i < outputs.size(); i++) {
    y(i) = outputs[i];
  }

  x.resize(inputs.size() / 2.0, 2);
  for (size_t i = 0; i < (inputs.size() / 2.0); i++) {
    x(i, 0) = inputs[2 * i];
    x(i, 1) = inputs[2 * i + 1];
  }

  data.push_back(x);
  data.push_back(y);
  data.push_back(beta);

  return data;
}

void test_settings(LMASettings &settings) {
  std::vector<MatX> data;
  MatX x;

  settings.max_iter = 100;
  settings.lambda = 0.01;
  settings.function = LMA_BIND(rosenbrock);
  settings.jacobian = LMA_BIND(rosenbrock_jacobian);
  settings.nb_inputs = 2;
  settings.nb_params = 2;

  data = generate_data();
  settings.x = data[0];
  settings.y = data[1];
  settings.beta = data[2];
}

TEST(LMAOpt, constructor) {
  LMAOpt opt;

  EXPECT_FALSE(opt.configured);
  EXPECT_EQ(100, opt.max_iter);
  EXPECT_FLOAT_EQ(0.01, opt.lambda);
  EXPECT_EQ(nullptr, opt.function);
  EXPECT_EQ(nullptr, opt.jacobian);
  EXPECT_EQ(0, opt.nb_inputs);
  EXPECT_EQ(0, opt.nb_params);

  EXPECT_FLOAT_EQ(0.0, opt.x(0, 0));
  EXPECT_FLOAT_EQ(0.0, opt.y(0));
  EXPECT_FLOAT_EQ(0.0, opt.beta(0));

  EXPECT_FLOAT_EQ(0.0, opt.y_est(0));
  EXPECT_FLOAT_EQ(0.0, opt.diff(0));

  EXPECT_FLOAT_EQ(0.0, opt.J(0));
  EXPECT_FLOAT_EQ(0.0, opt.H(0));

  EXPECT_EQ(FLT_MAX, opt.error);
}

TEST(LMAOpt, configure) {
  LMAOpt opt;
  LMASettings settings;

  test_settings(settings);
  opt.configure(settings);

  EXPECT_TRUE(opt.configured);
  EXPECT_EQ(settings.max_iter, opt.max_iter);
  EXPECT_FLOAT_EQ(settings.lambda, opt.lambda);
  EXPECT_NE(nullptr, opt.function);
  EXPECT_NE(nullptr, opt.jacobian);
  EXPECT_EQ(settings.nb_inputs, opt.nb_inputs);
  EXPECT_EQ(settings.nb_params, opt.nb_params);

  EXPECT_FLOAT_EQ(settings.x(0), opt.x(0));
  EXPECT_FLOAT_EQ(settings.y(0), opt.y(0));
  EXPECT_FLOAT_EQ(settings.beta(0), opt.beta(0));

  EXPECT_FLOAT_EQ(0.0, opt.y_est(0));
  EXPECT_FLOAT_EQ(0.0, opt.diff(0));

  EXPECT_FLOAT_EQ(0.0, opt.J(0, 0));
  EXPECT_FLOAT_EQ(0.0, opt.H(0, 0));

  EXPECT_EQ(FLT_MAX, opt.error);
}

TEST(LMAOpt, evalFunction) {
  LMAOpt opt;
  LMASettings settings;
  double error;

  // configure
  test_settings(settings);
  opt.configure(settings);

  // test
  opt.evalFunction(opt.beta, error);
  EXPECT_FLOAT_EQ(0.0, error);
}

TEST(LMAOpt, calcGradients) {
  LMAOpt opt;
  LMASettings settings;
  MatX J_before, H_before;

  // configure
  test_settings(settings);
  opt.configure(settings);
  J_before = opt.J;
  H_before = opt.H;

  // test
  opt.calcGradients(opt.beta);

  EXPECT_FALSE(J_before.isApprox(opt.J));
  EXPECT_FALSE(H_before.isApprox(opt.H));
}

TEST(LMAOpt, iterate) {
  LMAOpt opt;
  LMASettings settings;
  VecX beta_before;
  std::vector<VecX> data;

  // configure
  test_settings(settings);
  opt.configure(settings);

  opt.beta << 1.0, 90.0;
  beta_before = opt.beta;

  // test
  opt.evalFunction(opt.beta, opt.error);
  opt.calcGradients(opt.beta);

  std::cout << "beta: " << opt.beta.transpose() << std::endl;
  opt.iterate();
  std::cout << "beta: " << opt.beta.transpose() << std::endl;

  EXPECT_FALSE(beta_before.isApprox(opt.beta));
}

TEST(LMAOpt, optimize) {
  VecX beta;
  LMAOpt opt;
  LMASettings settings;
  std::vector<VecX> data;

  // configure
  test_settings(settings);
  settings.max_iter = 100;
  settings.beta << 1.01, 99.99;
  opt.configure(settings);

  opt.optimize();
  std::cout << opt.beta.transpose() << std::endl;
}

}  // namespace yarl
