#include "yarl/test.hpp"
#include "yarl/vision/chessboard.hpp"

namespace yarl {

TEST(Chessboard, constructor) {
  Chessboard chessboard;

  EXPECT_FALSE(chessboard.configured);

  EXPECT_EQ(0, chessboard.nb_corners_rows);
  EXPECT_EQ(0, chessboard.nb_corners_columns);
  EXPECT_EQ(0, chessboard.nb_corners_total);
  EXPECT_EQ(cv::Size(0, 0), chessboard.board_size);
}

TEST(Chessboard, configure) {
  Chessboard chessboard;

  chessboard.configure(1, 2);

  EXPECT_TRUE(chessboard.configured);

  EXPECT_EQ(2, chessboard.nb_corners_rows);
  EXPECT_EQ(1, chessboard.nb_corners_columns);
  EXPECT_EQ(2, chessboard.nb_corners_total);
  EXPECT_EQ(cv::Size(1, 2), chessboard.board_size);
}

}  // end of yarl namespace
