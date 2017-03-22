#ifndef VISION_CHESSBOARD_HPP
#define VISION_CHESSBOARD_HPP

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <opencv2/opencv.hpp>

#include "battery/utils/logging.hpp"
#include "battery/utils/utils.hpp"

namespace battery {

class Chessboard {
public:
  bool configured;

  int nb_corners_rows;
  int nb_corners_columns;
  int nb_corners_total;
  cv::Size board_size;

  Chessboard(void);
  int configure(int nb_corners_columns, int nb_corners_rows);
};

} // end of battery namespace
#endif
