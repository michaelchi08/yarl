#include "battery/battery_test.hpp"
#include "battery/vision/chessboard.hpp"

namespace battery {

TEST(Chessboard, constructor) {
  Chessboard chessboard;

  ASSERT_EQ(false, chessboard.configured);

  ASSERT_EQ(0, chessboard.nb_corners_rows);
  ASSERT_EQ(0, chessboard.nb_corners_columns);
  ASSERT_EQ(0, chessboard.nb_corners_total);
  ASSERT_EQ(cv::Size(0, 0), chessboard.board_size);
}

TEST(Chessboard, configure) {
  Chessboard chessboard;

  chessboard.configure(1, 2);

  ASSERT_EQ(true, chessboard.configured);

  ASSERT_EQ(2, chessboard.nb_corners_rows);
  ASSERT_EQ(1, chessboard.nb_corners_columns);
  ASSERT_EQ(2, chessboard.nb_corners_total);
  ASSERT_EQ(cv::Size(1, 2), chessboard.board_size);
}

} // end of battery namespace
