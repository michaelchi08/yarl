#ifndef YARL_VISION_EIGHT_POINT_HPP
#define YARL_VISION_EIGHT_POINT_HPP

#include <iostream>
#include <vector>

#include <math.h>

#include "yarl/utils/math.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/vision/utils.hpp"

namespace yarl {

/**
 * Eight Point Algorithm
 */
class EightPoint {
public:
  bool configured;

  int image_width;
  int image_height;
  Mat3 N;

  EightPoint() : configured(false), image_width(0), image_height(0), N() {}

  int configure(int image_width, int image_height);
  void normalizePoints(MatX &pts1, MatX &pts2);
  void formMatrixA(const MatX &pts1, const MatX &pts2, MatX &A);
  void approximateFundamentalMatrix(const MatX &A, MatX &F);
  void refineFundamentalMatrix(MatX &F);
  void denormalizeFundamentalMatrix(MatX &F);
  int estimate(MatX &pts1, MatX &pts2, MatX &F);
  int estimate(MatX &pts1, MatX &pts2, Mat3 &K, Mat3 &E);
  int obtainPossiblePoses(Mat3 &E, std::vector<MatX> &poses);
  int obtainPose(Vec3 &pt1,
                 Vec3 &pt2,
                 Mat3 &K1,
                 Mat3 &K2,
                 std::vector<MatX> &poses,
                 MatX &pose);
};

}  // namespace yarl
#endif
