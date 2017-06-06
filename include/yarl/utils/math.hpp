#ifndef YARL_UTILS_MATH_HPP
#define YARL_UTILS_MATH_HPP

#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace yarl {

#ifndef EIGEN_TYPEDEF
#define EIGEN_TYPEDEF
typedef Eigen::Vector2d Vec2;
typedef Eigen::Vector3d Vec3;
typedef Eigen::Vector4d Vec4;
typedef Eigen::VectorXd VecX;

typedef Eigen::Matrix2d Mat2;
typedef Eigen::Matrix3d Mat3;
typedef Eigen::Matrix4d Mat4;
typedef Eigen::MatrixXd MatX;

typedef Eigen::Quaterniond Quaternion;
#endif

/**
 * Eigen vector comparator
 */
struct VecComparator {
  bool operator()(const VecX &a, const VecX &b) const {
    return std::lexicographical_compare(
      a.data(), a.data() + a.size(), b.data(), b.data() + b.size());
  }
};

/**
 * Eigen matrix comparator
 */
struct MatComparator {
  bool operator()(const MatX &a, const MatX &b) const {
    return std::lexicographical_compare(
      a.data(), a.data() + a.size(), b.data(), b.data() + b.size());
  }
};


int sign(double x);

/**
 * Generates random integer or float with a upper bound `ub` and lower bound
 * `lb` using a uniform random distribution.
 */
int randi(int ub, int lb);
double randf(double ub, double lb);

/**
 * Compares two floating point numbers `f1` and `f2` with an error threshold
 * defined by `threshold`.
 *
 * Returns:
 *
 * - `0`: If `f1` == `f2` or the difference is less then `threshold`
 * - `1`: If `f1` > `f2`
 * - `-1`: If `f1` < `f2`
 */
int fltcmp(double f1, double f2);

/**
 * Calculates and returns the median of double array `v`.
 */
double median(std::vector<double> &v);

/**
 * Convert degrees `d` to radians `r` and vice versa.
 */
double deg2rad(double d);
double rad2deg(double r);

/**
 * Load matrix from `std::vector<double>` or `MatX` and vice versa.
 */
void load_matrix(const std::vector<double> &x, int rows, int cols, MatX &y);
void load_matrix(const MatX &A, std::vector<double> &x);

/**
 * Convert euler roll, pitch and yaw according to `euler_seq` to rotation
 * matrix `R` or quaternion `q`
 */
int euler2rot(const Vec3 &euler, int euler_seq, Mat3 &R);
int euler2quat(const Vec3 &euler, int euler_seq, Quaternion &q);

/**
 * Convert quaternion to euler roll, pitch and yaw.
 */
int quat2euler(const Quaternion &q, int euler_seq, Vec3 &euler);
int quat2rot(const Quaternion &q, Mat3 &R);

void enu2nwu(const Vec3 &enu, Vec3 &nwu);
void cf2nwu(const Vec3 &cf, Vec3 &nwu);
void cf2enu(const Vec3 &cf, Vec3 &nwu);
void ned2enu(const Vec3 &ned, Vec3 &enu);
void ned2nwu(const Quaternion &ned, Quaternion &enu);
void nwu2enu(const Vec3 &nwu, Vec3 &enu);
void nwu2ned(const Quaternion &nwu, Quaternion &ned);
void nwu2edn(const Vec3 &nwu, Vec3 &edn);

void target2body(const Vec3 &target_pos_if,
                 const Vec3 &body_pos_if,
                 const Quaternion &body_orientation_if,
                 Vec3 &target_pos_bf);
void target2body(const Vec3 &target_pos_if,
                 const Vec3 &body_pos_if,
                 const Vec3 &body_euler_if,
                 Vec3 &target_pos_bf);
void target2bodyplanar(const Vec3 &target_pos_if,
                       const Vec3 &body_pos_if,
                       const Quaternion &body_orientation_if,
                       Vec3 &target_pos_bf);
void target2bodyplanar(const Vec3 &target_pos_if,
                       const Vec3 &body_pos_if,
                       const Vec3 &body_euler_if,
                       Vec3 &target_pos_bf);
void target2inertial(const Vec3 &target_pos_bf,
                     const Vec3 &body_pos_if,
                     const Vec3 &body_euler_if,
                     Vec3 &target_pos_if);
void target2inertial(const Vec3 &target_pos_bf,
                     const Vec3 &body_pos_if,
                     const Quaternion &body_orientation_if,
                     Vec3 &target_pos_if);
void inertial2body(const Vec3 &enu_if,
                   const Quaternion &orientation_if,
                   Vec3 &nwu_bf);
void inertial2body(const Vec3 &enu_if,
                   const Vec3 &orientation_if,
                   Vec3 &nwu_bf);

/// Wraps `euler_angle` to 180 or 360.
double wrapTo180(double euler_angle);
double wrapTo360(double euler_angle);

double cross_track_error(const Vec2 &p1, const Vec2 &p2, const Vec2 &pos);

int point_left_right(const Vec2 &p1, const Vec2 &p2, const Vec2 &pos);
double closest_point(const Vec2 &p1,
                     const Vec2 &p2,
                     const Vec2 &p3,
                     Vec2 &closest);
Vec2 linear_interpolation(const Vec2 &a, const Vec2 &b, double mu);

}  // namespace yarl
#endif
