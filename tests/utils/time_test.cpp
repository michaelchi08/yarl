#include "yarl/test.hpp"
#include "yarl/utils/time.hpp"

namespace yarl {

TEST(Utils, ticAndToc) {
  struct timespec start;

  tic(&start);
  usleep(10 * 1000);
  EXPECT_TRUE(toc(&start) < 0.011);
  EXPECT_TRUE(toc(&start) > 0.009);
  EXPECT_TRUE(mtoc(&start) < 11.0);
  EXPECT_TRUE(mtoc(&start) > 9.0);
}

}  // end of yarl namespace
