#ifndef YARL_OPTIMIZATION_CERES_CERES_EXAMPLES_HPP
#define YARL_OPTIMIZATION_CERES_CERES_EXAMPLES_HPP

#include <ceres/ceres.h>

namespace yarl {

struct AutoDiffCostFunctor {
  template <typename T>
  bool operator()(const T *const x, T *residual) const {
    residual[0] = T(10.0) - x[0];
    return true;
  }
};

struct NumericalDiffCostFunctor {
  template <typename T>
  bool operator()(const T *const x, T *residual) const {
    residual[0] = T(10.0) - x[0];
    return true;
  }
};

class AnalyticalCostFunction : public ceres::SizedCostFunction<1, 1> {
public:
  virtual ~AnalyticalCostFunction() {}
  virtual bool Evaluate(double const *const *parameters,
                        double *residuals,
                        double **jacobians) const {
    const double x = parameters[0][0];
    residuals[0] = 10 - x;

    // Compute the Jacobian if asked for.
    if (jacobians != NULL && jacobians[0] != NULL) {
      jacobians[0][0] = -1;
    }
    return true;
  }
};

struct CurveFittingResidual {
  CurveFittingResidual(double x, double y) : x(x), y(y) {}
  template <typename T>
  bool operator()(const T *const m, const T *const c, T *residual) const {
    residual[0] = this->y - exp(m[0] * this->x + c[0]);
    return true;
  }

private:
  const double x;
  const double y;
};

/**
 * `yarl.ceres.ceres_examples` contains three functions `void
 * runAutoDiffExample(void);`, `void runNumericalDiffExample(void);` and `void
 * runAnalyticalDiffExample(void);` that run the automatic differentiation,
 * numerical differentiation and analytical differentiation nonlinear least
 * squares optimization problem on the following cost function.
 *
 * \begin{equation}
 *   f(x) = (10 - x)
 * \end{equation}
 *
 * Where the minimum is located at $x = 10$.
 */
void runAutoDiffExample();
void runNumericalDiffExample();
void runAnalyticalDiffExample();
void runCurveFittingExample();

}  // end of yarl namespace
#endif
