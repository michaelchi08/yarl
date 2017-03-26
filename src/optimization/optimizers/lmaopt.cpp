#include "yarl/optimization/optimizers/lmaopt.hpp"

namespace yarl {

void lmaopt_default_settings(struct lmaopt_settings *settings) {
  settings->max_iter = 100;
  settings->lambda = 0.01;
  settings->function = nullptr;
  settings->jacobian = nullptr;
  settings->nb_inputs = 0;
  settings->nb_params = 0;

  settings->x = MatX::Zero(1, 1);
  settings->y = MatX::Zero(1, 1);
  settings->beta = MatX::Zero(1, 1);
}

void lmaopt_setup(struct lmaopt *opt) {
  opt->max_iter = 100;
  opt->lambda = 0.01;
  opt->function = nullptr;
  opt->jacobian = nullptr;
  opt->nb_inputs = 0;
  opt->nb_params = 0;

  opt->x = MatX::Zero(1, 1);
  opt->y = MatX::Zero(1, 1);
  opt->beta = MatX::Zero(1, 1);

  opt->y_est = MatX::Zero(1, 1);
  opt->diff = MatX::Zero(1, 1);

  opt->J = MatX::Zero(1, 1);
  opt->H = MatX::Zero(1, 1);

  opt->error = FLT_MAX;
}

int lmaopt_configure(struct lmaopt *opt, struct lmaopt_settings *settings) {
  opt->max_iter = settings->max_iter;
  opt->lambda = settings->lambda;
  opt->function = settings->function;
  opt->jacobian = settings->jacobian;
  opt->nb_inputs = settings->nb_inputs;
  opt->nb_params = settings->nb_params;

  opt->x = settings->x;
  opt->y = settings->y;
  opt->beta = settings->beta;

  opt->y_est = MatX::Zero(opt->y.rows(), 1);
  opt->diff = MatX::Zero(opt->y.rows(), 1);

  opt->J = MatX::Zero(opt->y.rows(), opt->nb_params);
  opt->H = MatX::Zero(opt->nb_params, opt->nb_params);

  opt->error = FLT_MAX;

  return 0;
}

int lmaopt_evaluate_function(struct lmaopt *opt, VecX beta, double *error) {
  // evaluate function
  for (int i = 0; i < opt->y.rows(); i++) {
    opt->y_est(i) = opt->function(
      opt->x.block(i, 0, 1, opt->nb_inputs).transpose(), opt->beta);
  }

  // calculate error
  opt->diff = opt->y - opt->y_est;
  *error = opt->diff.dot(opt->diff);

  return 0;
}

int lmaopt_calculate_gradient(struct lmaopt *opt, VecX beta) {
  // calculate jacobian
  for (int i = 0; i < opt->y.rows(); i++) {
    opt->J.block(i, 0, 1, opt->nb_params) =
      opt->jacobian(opt->x.block(i, 0, 1, opt->nb_inputs).transpose(), beta)
        .transpose();
  }

  // approximate Hessian
  opt->H = opt->J.transpose() * opt->J;

  return 0;
}

int lmaopt_iterate(struct lmaopt *opt) {
  MatX I, H_est, I_adaptive;
  VecX delta, beta_est;
  double error_est;

  // Levenberg (1994) - damp hessian
  // I = MatX::Identity(opt->nb_params, opt->nb_params);
  // H_est = opt->H + opt->lambda * I;

  // Marquardt (1963) - adaptive component-wise damping
  I = MatX::Identity(opt->nb_params, opt->nb_params);
  I.diagonal() = opt->H.diagonal();
  H_est = opt->H + opt->lambda * I;

  // update params
  delta = -H_est.inverse() * (opt->J.transpose() * opt->diff);
  beta_est = opt->beta + delta;

  // evaluate new error
  lmaopt_evaluate_function(opt, beta_est, &error_est);

  // adjust damping factor
  if (error_est > opt->error) {
    opt->lambda *= 10.0;

  } else {
    opt->lambda /= 10.0;
    opt->beta = beta_est;
    opt->error = error_est;
    lmaopt_calculate_gradient(opt, beta_est);
  }

  return 0;
}

int lmaopt_optimize(struct lmaopt *opt) {
  try {
    // initialize error and gradients
    lmaopt_evaluate_function(opt, opt->beta, &opt->error);
    lmaopt_calculate_gradient(opt, opt->beta);

    // iterate
    for (int i = 0; i < opt->max_iter; i++) {
      lmaopt_iterate(opt);
    }

  } catch (const std::bad_function_call &e) {
    log_err(ELMAF, e.what());
    return -2;
  }

  return 0;
}

}  // end of yarl namespace
