#ifndef YARL_VISION_MODELS_HPP
#define YARL_VISION_MODELS_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {


/**
 * Base Camera Model
 */
class CameraModel {
public:
  Vec3 t;
  union {
    Mat3 R;
    Quaternion q;
  };

  CameraModel() : t{Vec3::Zero()}, R{Mat3::Identity()} {}
  CameraModel(const Vec3 &t, const Mat3 &R) : t{t}, R{R} {}
  CameraModel(const Vec3 &t, const Quaternion &q) : t{t}, q{q} {}
};

/**
 * Pinhole Camera Model
 */
class PinholeModel : public CameraModel {
public:
  Mat3 K;

  PinholeModel() : CameraModel{}, K{Mat3::Identity()} {}
  explicit PinholeModel(const Mat3 &K) : CameraModel{}, K{K} {}
  PinholeModel(const Mat3 &K, const Vec3 &t, const Mat3 &R)
    : CameraModel{t, R}, K{K} {}

  /**
   * Project
   */
  int project();
};


}  // namespace yarl
#endif
