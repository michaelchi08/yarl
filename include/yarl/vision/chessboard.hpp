#ifndef YARL_VISION_CHESSBOARD_HPP
#define YARL_VISION_CHESSBOARD_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "yarl/utils/utils.hpp"

namespace yarl {

struct Chessboard {
  bool configured;

  int nb_corners_rows;
  int nb_corners_columns;
  int nb_corners_total;
  cv::Size board_size;

  Chessboard();
  int configure(int nb_corners_columns, int nb_corners_rows);
};

}  // end of yarl namespace
#endif
