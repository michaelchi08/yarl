#include "yarl/test.hpp"
#include "yarl/optimization/optimizers/ransac.hpp"
#include "yarl/utils/data.hpp"
#include "yarl/utils/math.hpp"

#define TEST_DATA "tests/data/optimization/optimizers/ransac/sample.dat"

namespace yarl {

TEST(RANSAC, constructor) {
  RANSAC ransac;

  ASSERT_FALSE(ransac.configured);

  ASSERT_EQ(ransac.max_iter, 0);
  ASSERT_FLOAT_EQ(ransac.thresh_ratio, 1.0);
  ASSERT_FLOAT_EQ(ransac.thresh_dist, 0.0);

  ASSERT_EQ(ransac.iter, 0);
  ASSERT_EQ(ransac.max_inliers, 0);
  ASSERT_FLOAT_EQ(ransac.model_params[0], 0.0);
  ASSERT_FLOAT_EQ(ransac.model_params[1], 0.0);
}

TEST(RANSAC, configure) {
  RANSAC ransac;

  ransac.configure(10, 0.8, 0.1);

  ASSERT_TRUE(ransac.configured);

  ASSERT_EQ(ransac.max_iter, 10);
  ASSERT_FLOAT_EQ(ransac.thresh_ratio, 0.8);
  ASSERT_FLOAT_EQ(ransac.thresh_dist, 0.1);

  ASSERT_EQ(ransac.iter, 0);
  ASSERT_EQ(ransac.max_inliers, 0);
  ASSERT_FLOAT_EQ(ransac.model_params[0], 0.0);
  ASSERT_FLOAT_EQ(ransac.model_params[1], 0.0);
}

TEST(RANSAC, RandomSample) {
  int retval;
  Vec2 sample;
  MatX data(2, 100);
  RANSAC ransac;

  // setup
  for (int i = 0; i < 100; i++) {
    data(0, i) = rand() % 100;
    data(1, i) = rand() % 100;
  }
  ransac.configure(10, 0.8, 0.1);

  // test and assert
  sample << -1, -1;
  retval = ransac.randomSample(data, sample);

  ASSERT_EQ(retval, 0);
  ASSERT_NE(sample(0), -1);
  ASSERT_NE(sample(1), -1);
}

TEST(RANSAC, computeDistances) {
  int retval;
  MatX data(2, 100);
  Vec2 p1;
  Vec2 p2;
  VecX dists;
  RANSAC ransac;

  // setup
  for (int i = 0; i < 100; i++) {
    data(0, i) = i;
    data(1, i) = i;
  }
  ransac.configure(10, 0.8, 0.1);

  // test and assert
  ransac.randomSample(data, p1);
  ransac.randomSample(data, p2);
  retval = ransac.computeDistances(data, p1, p2, dists);

  ASSERT_EQ(retval, 0);
}

TEST(RANSAC, computeInliers) {
  int retval;
  RANSAC ransac;
  VecX dists(10);

  // setup
  dists << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0;
  ransac.configure(10, 0.8, 0.5);

  // test and assert
  retval = ransac.computeInliers(dists);
  ASSERT_EQ(retval, 0);
  ASSERT_EQ((int) ransac.inliers.size(), 5);
  ASSERT_EQ(ransac.inliers[0], 0);
  ASSERT_EQ(ransac.inliers[1], 1);
  ASSERT_EQ(ransac.inliers[2], 2);
  ASSERT_EQ(ransac.inliers[3], 3);
  ASSERT_EQ(ransac.inliers[4], 4);
}

TEST(RANSAC, update) {
  int retval;
  RANSAC ransac;
  Vec2 p1;
  Vec2 p2;

  // setup
  ransac.configure(10, 0.8, 0.5);
  ransac.threshold = 2;
  ransac.max_inliers = 3;
  ransac.inliers.push_back(0);
  ransac.inliers.push_back(1);
  ransac.inliers.push_back(2);
  ransac.inliers.push_back(3);
  p1 << 1.0, 2.0;
  p2 << 3.0, 4.0;

  // test and assert
  retval = ransac.update(p1, p2);
  ASSERT_EQ(ransac.max_inliers, 4);
  ASSERT_EQ(retval, 0);
  ASSERT_FLOAT_EQ(ransac.model_params[0], 1.0);
  ASSERT_FLOAT_EQ(ransac.model_params[1], 1.0);
}

TEST(RANSAC, optimize) {
  MatX data;
  MatX x;
  RANSAC ransac;

  // setup
  csv2mat(TEST_DATA, true, data);
  x = data.transpose();
  ransac.configure(40, 0.5, 5);

  // test and assert
  clock_t begin = clock();
  ransac.optimize(x);
  clock_t end = clock();

  double secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "elasped: " << secs << " seconds" << std::endl;

  ASSERT_TRUE(ransac.model_params[0] < 23);
  ASSERT_TRUE(ransac.model_params[0] > 18);
  ASSERT_TRUE(ransac.model_params[1] < 13);
  ASSERT_TRUE(ransac.model_params[1] > 8);
}

}  // end of yarl namespace
