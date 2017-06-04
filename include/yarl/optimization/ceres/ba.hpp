#ifndef YARL_OPTIMIZATION_CERES_BA_HPP
#define YARL_OPTIMIZATION_CERES_BA_HPP

#include <typeinfo>

#include <ceres/ceres.h>

#include "yarl/optimization/ceres/extensions.hpp"
#include "yarl/utils/utils.hpp"

namespace yarl {

class BAResidual {
public:
  double fx;
  double fy;
  double cx;
  double cy;

  double x;
  double y;

  bool origin;

  BAResidual()
    : fx(0.0), fy(0.0), cx(0.0), cy(0.0), x(0.0), y(0.0), origin(false) {}

  BAResidual(Mat3 K, Vec2 x, bool origin)
    : fx(K(0, 0)),
      fy(K(1, 1)),
      cx(K(0, 2)),
      cy(K(1, 2)),
      x(x(0)),
      y(x(1)),
      origin(origin) {}

  template <typename T>
  bool operator()(const T *const q,
                  const T *const c,
                  const T *const x,
                  T *residual) const {
    // camera intrinsics matrix
    Eigen::Matrix<T, 3, 3> K;
    K(0, 0) = T(this->fx);
    K(0, 1) = T(0.0);
    K(0, 2) = T(this->cx);

    K(1, 0) = T(0.0);
    K(1, 1) = T(this->fy);
    K(1, 2) = T(this->cy);

    K(2, 0) = T(0.0);
    K(2, 1) = T(0.0);
    K(2, 2) = T(1.0);

    // rotation matrix from quaternion q = (x, y, z, w)
    Eigen::Matrix<T, 3, 3> R;
    R(0, 0) = T(1) - T(2) * pow(q[1], 2) - T(2) * pow(q[2], 2);
    R(0, 1) = T(2) * q[0] * q[1] + T(2) * q[3] * q[2];
    R(0, 2) = T(2) * q[0] * q[2] - T(2) * q[3] * q[1];

    R(1, 0) = T(2) * q[0] * q[1] - T(2) * q[3] * q[2];
    R(1, 1) = T(1) - T(2) * pow(q[0], 2) - T(2) * pow(q[2], 2);
    R(1, 2) = T(2) * q[1] * q[2] + T(2) * q[3] * q[2];

    R(2, 0) = T(2) * q[0] * q[2] - T(2) * q[3] * q[1];
    R(2, 1) = T(2) * q[1] * q[2] - T(2) * q[3] * q[0];
    R(2, 2) = T(1) - T(2) * pow(q[0], 2) - T(2) * pow(q[1], 2);

    // camera center
    Eigen::Matrix<T, 3, 1> C = Eigen::Matrix<T, 3, 1>{c[0], c[1], c[2]};

    // 3D point
    Eigen::Matrix<T, 3, 1> X = Eigen::Matrix<T, 3, 1>{x[0], x[1], x[2]};

    // calculate reprojection error
    Eigen::Matrix<T, 3, 1> x_est;
    if (origin) {
      x_est = K * X;  // for image 1
    } else {
      x_est = K * R * (X - C);  // for image 2 and beyond
    }

    // convert predicted 2d point in homogenous coordinates
    // back to image coordinates
    Eigen::Matrix<T, 2, 1> x_est_pixel;
    x_est_pixel(0) = x_est(0) / x_est(2);
    x_est_pixel(1) = x_est(1) / x_est(2);

    // calculate residual error
    residual[0] = abs(T(this->x) - x_est_pixel(0));
    residual[1] = abs(T(this->y) - x_est_pixel(1));

    return true;
  }
};

// class BAAnalyticalResidual : public ::ceres::SizedCostFunction<2, 4, 3, 3>
// {
// public:
//   double fx;
//   double fy;
//   double cx;
//   double cy;
//
//   double x;
//   double y;
//
//   bool origin;
//
//   BAAnalyticalResidual()
//     : fx(0.0),
//       fy(0.0),
//       cx(0.0),
//       cy(0.0),
//
//       x(0.0),
//       y(0.0),
//
//       origin(false) {}
//
//   BAAnalyticalResidual(Mat3 K, Vec2 x, bool origin)
//     : fx(K(0, 0)),
//       fy(K(1, 1)),
//       cx(K(0, 2)),
//       cy(K(1, 2)),
//
//       x(x(0)),
//       y(x(1)),
//
//       origin(origin) {}
//
//   virtual ~BAAnalyticalResidual() {}
//
//   inline void setupCameraInstrinsicsMatrix(Eigen::Matrix3d &K) {
//     K(0, 0) = this->fx;
//     K(0, 1) = 0.0;
//     K(0, 2) = this->cx;
//
//     K(1, 0) = 0.0;
//     K(1, 1) = this->fy;
//     K(1, 2) = this->cy;
//
//     K(2, 0) = 0.0;
//     K(2, 1) = 0.0;
//     K(2, 2) = 1.0;
//   }
//
//   inline void setupRotationMatrixFromQuaternion(const double *q,
//                                                 Eigen::Matrix3d &R) {
//     // rotation matrix from quaternion q = (x, y, z, w)
//     R(0, 0) = 1.0 - 2.0 * pow(q[1], 2.0) - 2.0 * pow(q[2], 2.0);
//     R(0, 1) = 2.0 * q[0] * q[1] + 2.0 * q[3] * q[2];
//     R(0, 2) = 2.0 * q[0] * q[2] - 2.0 * q[3] * q[1];
//
//     R(1, 0) = 2.0 * q[0] * q[1] - 2.0 * q[3] * q[2];
//     R(1, 1) = 1.0 - 2.0 * pow(q[0], 2.0) - 2.0 * pow(q[2], 2.0);
//     R(1, 2) = 2.0 * q[1] * q[2] + 2.0 * q[3] * q[2];
//
//     R(2, 0) = 2.0 * q[0] * q[2] - 2.0 * q[3] * q[1];
//     R(2, 1) = 2.0 * q[1] * q[2] - 2.0 * q[3] * q[0];
//     R(2, 2) = 1.0 - 2.0 * pow(q[0], 2.0) - 2.0 * pow(q[1], 2.0);
//   }
//
//   inline void setupCameraCenter(const double *c, Eigen::Matrix3d &C) {
//     C << c[0], c[1], c[2];
//   }
//
//   inline void setup3DPoint(const double *x, Eigen::Matrix3d &X) {
//     X << x[0], x[1], x[2];
//   }
//
//   inline void calculateReprojectionError(double const *const *parameters,
//                                          double *residuals) {
//     Eigen::Matrix3d K, R;
//     Eigen::Vector3d C, X;
//     Eigen::Vector3d x_est;
//     Eigen::Vector2d x_est_pixel;
//
//     // setup
//     this->setupCameraInstrinsicsMatrix(K);
//     this->setupRotationMatrixFromQuaternion(parameters[0]);
//     this->setupCameraCenter(parameters[1], C);
//     this->setup3DPoint(parameters[2], X);
//
//     // calculate reprojection error
//     if (origin) {
//       x_est = K * X;  // for image 1
//     } else {
//       x_est = K * R * (X - C);  // for image 2 and beyond
//     }
//
//     // convert predicted 2d point in homogenous coordinates
//     // back to image coordinates
//     x_est_pixel << x_est(0) / x_est(2), x_est(1) / x_est(2);
//
//     // calculate residual error
//     residuals[0] = abs(this->x - x_est_pixel(0));
//     residuals[1] = abs(this->y - x_est_pixel(1));
//   }
//
//   virtual bool Evaluate(double const *const *parameters,
//                         double *residuals,
//                         double **jacobians) {
//     // this->calculateReprojectionError(parameters, residuals);
//
//     UNUSED(parameters);
//     UNUSED(residuals);
//     UNUSED(jacobians);
//
//     return true;
//   }
// };

class BundleAdjustment {
public:
  bool configured;

  Mat3 K;
  MatX x1_pts;
  MatX x2_pts;

  double **q;
  double **c;
  double **x;

  BundleAdjustment()
    : configured(false), K(), x1_pts(), x2_pts(), q(NULL), c(NULL), x(NULL) {
    this->K = MatX::Zero(3, 3);
    this->x1_pts.resize(0, 0);
    this->x2_pts.resize(0, 0);
  }

  ~BundleAdjustment() {
    if (this->configured) {
      for (int i = 0; i < this->x1_pts.rows(); i++) {
        free(this->x[i]);
      }
      free(this->q[0]);
      free(this->q[1]);

      free(this->c[0]);
      free(this->c[1]);

      free(this->x);
      free(this->q);
      free(this->c);
    }
  }

  int configure(Mat3 K, MatX x1_pts, MatX x2_pts);
  int solve();
};

}  // namespace yarl
#endif
