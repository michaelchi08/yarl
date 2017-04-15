#ifndef YARL_UTILS_MATH_HPP
#define YARL_UTILS_MATH_HPP

#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace yarl {

#ifndef __EIGEN_TYPEDEF__
#define __EIGEN_TYPEDEF__
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

int sign(double x);
int randi(int ub, int lb);
double randf(double ub, double lb);
int fltcmp(double f1, double f2);
double median(std::vector<double> &v);
double deg2rad(double d);
double rad2deg(double r);
void load_matrix(const std::vector<double> &x, int rows, int cols, MatX &y);
void load_matrix(const MatX &A, std::vector<double> &x);
int euler2rot(const Vec3 &euler, int euler_seq, Mat3 &R);
int euler2quat(const Vec3 &euler, int euler_seq, Quaternion &q);
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
double wrapTo180(double euler_angle);
double wrapTo360(double euler_angle);
double cross_track_error(const Vec2 &p1, const Vec2 &p2, const Vec2 &pos);
int point_left_right(const Vec2 &p1, const Vec2 &p2, const Vec2 &pos);
double closest_point(const Vec2 &p1,
                     const Vec2 &p2,
                     const Vec2 &p3,
                     Vec2 &closest);
Vec2 linear_interpolation(const Vec2 &a, const Vec2 &b, double mu);

}  // end of yarl namespace
#endif
