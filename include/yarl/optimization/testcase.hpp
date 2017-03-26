#ifndef YARL_OPTIMIZATION_BENCHMARK_HPP
#define YARL_OPTIMIZATION_BENCHMARK_HPP

#include <iostream>
#include <random>

#include "yarl/utils/utils.hpp"

namespace yarl {

class TestRange {
public:
  double x_min;
  double x_max;

  double y_min;
  double y_max;

  double z_min;
  double z_max;

  TestRange(void);
};

class TestCase {
public:
  bool configured;

  TestCase(void);
  int configure(void);
  void createR(double roll, double pitch, double yaw, Mat3 &R);
  void createR(double qx, double qy, double qz, double qw, Mat3 &R);
  void createP(Mat3 K, Mat3 R, Vec3 t, MatX &P);
  void generateRandom3DPoints(TestRange range, int nb_pts, yarl::MatX &pts);
  void project3DTo2D(MatX P, MatX pts_3d, MatX &pts_2d);
  void project3DTo2D(Mat3 K, Mat3 R, Vec3 t, MatX pts_3d, MatX &pts_2d);
  void generateTestCase(TestRange range, MatX &pts1, MatX &pts2, MatX &pts3d);
};

}  // end of yarl namespace
#endif
