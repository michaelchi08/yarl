#ifndef YARL_VISION_MODELS_HPP
#define YARL_VISION_MODELS_HPP

#include "yarl/utils/utils.hpp"

namespace yarl {

/**
 * Pinhole Camera Model
 */
class PinholeModel {
public:
  Mat3 K;
  Mat3 R;
  Vec3 t;

  PinholeModel()
    : K{Mat3::Identity()}, R{Mat3::Identity()}, t{Vec3::Zero()} {}

  /**
   * Project
   */
  int project();

  /**
   * Normalize
   */
  int normalize();
};


}  // end of yarl namespace
#endif
