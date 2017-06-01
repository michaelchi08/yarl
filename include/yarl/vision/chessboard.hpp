#ifndef YARL_VISION_CHESSBOARD_HPP
#define YARL_VISION_CHESSBOARD_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "yarl/utils/utils.hpp"

namespace yarl {

/**
 * Chessboard
 */
struct Chessboard {
  bool configured;

  int nb_corners_rows;
  int nb_corners_columns;
  int nb_corners_total;
  cv::Size board_size;

  Chessboard()
    : configured(false),
      nb_corners_rows(0),
      nb_corners_columns(0),
      nb_corners_total(0),
      board_size(0, 0) {}

  int configure(int nb_corners_columns, int nb_corners_rows);
};

}  // namespace yarl
#endif
