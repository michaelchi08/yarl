#include "yarl/test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/optimization/optimizers/ransac.hpp"

#define TEST_DATA "tests/data/optimization/optimizers/ransac/sample.dat"

namespace yarl {

TEST(ransac, setup) {
  struct ransac opt;

  ransac_setup(&opt);
  ASSERT_FALSE(opt.configured);

  ASSERT_EQ(opt.max_iter, 0);
  ASSERT_FLOAT_EQ(opt.thresh_ratio, 1.0);
  ASSERT_FLOAT_EQ(opt.thresh_dist, 0.0);

  ASSERT_EQ(opt.iter, 0);
  ASSERT_EQ(opt.max_inliers, 0);
  ASSERT_FLOAT_EQ(opt.model_params[0], 0.0);
  ASSERT_FLOAT_EQ(opt.model_params[1], 0.0);
}

TEST(ransac, configure) {
  struct ransac opt;

  ransac_setup(&opt);
  ransac_configure(&opt, 10, 0.8, 0.1);

  ASSERT_EQ(opt.configured, true);

  ASSERT_EQ(opt.max_iter, 10);
  ASSERT_FLOAT_EQ(opt.thresh_ratio, 0.8);
  ASSERT_FLOAT_EQ(opt.thresh_dist, 0.1);

  ASSERT_EQ(opt.iter, 0);
  ASSERT_EQ(opt.max_inliers, 0);
  ASSERT_FLOAT_EQ(opt.model_params[0], 0.0);
  ASSERT_FLOAT_EQ(opt.model_params[1], 0.0);
}

TEST(ransac, randomSample) {
  int retval;
  Vec2 sample;
  MatX data(2, 100);
  struct ransac opt;

  // setup
  for (int i = 0; i < 100; i++) {
    data(0, i) = rand() % 100;
    data(1, i) = rand() % 100;
  }
  ransac_setup(&opt);
  ransac_configure(&opt, 10, 0.8, 0.1);

  // test and assert
  sample << -1, -1;
  retval = ransac_random_sample(&opt, data, sample);

  ASSERT_EQ(retval, 0);
  ASSERT_NE(sample(0), -1);
  ASSERT_NE(sample(1), -1);
}

TEST(ransac, compute_distances) {
  int retval;
  MatX data(2, 100);
  Vec2 p1;
  Vec2 p2;
  VecX dists;
  struct ransac opt;

  // setup
  for (int i = 0; i < 100; i++) {
    data(0, i) = i;
    data(1, i) = i;
  }
  ransac_configure(&opt, 10, 0.8, 0.1);

  // test and assert
  ransac_random_sample(&opt, data, p1);
  ransac_random_sample(&opt, data, p2);
  retval = ransac_compute_distances(&opt, data, p1, p2, dists);

  ASSERT_EQ(retval, 0);
}

TEST(ransac, compute_inliers) {
  int retval;
  struct ransac opt;
  VecX dists(10);

  // setup
  dists << 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0;
  ransac_setup(&opt);
  ransac_configure(&opt, 10, 0.8, 0.5);

  // test and assert
  retval = ransac_compute_inliers(&opt, dists);
  ASSERT_EQ(retval, 0);
  ASSERT_EQ((int) opt.inliers.size(), 5);
  ASSERT_EQ(opt.inliers[0], 0);
  ASSERT_EQ(opt.inliers[1], 1);
  ASSERT_EQ(opt.inliers[2], 2);
  ASSERT_EQ(opt.inliers[3], 3);
  ASSERT_EQ(opt.inliers[4], 4);
}

TEST(ransac, update) {
  int retval;
  struct ransac opt;
  Vec2 p1;
  Vec2 p2;

  // setup
  ransac_setup(&opt);
  ransac_configure(&opt, 10, 0.8, 0.5);
  opt.threshold = 2;
  opt.max_inliers = 3;
  opt.inliers.push_back(0);
  opt.inliers.push_back(1);
  opt.inliers.push_back(2);
  opt.inliers.push_back(3);
  p1 << 1.0, 2.0;
  p2 << 3.0, 4.0;

  // test and assert
  retval = ransac_update(&opt, p1, p2);
  ASSERT_EQ(opt.max_inliers, 4);
  ASSERT_EQ(retval, 0);
  ASSERT_FLOAT_EQ(opt.model_params[0], 1.0);
  ASSERT_FLOAT_EQ(opt.model_params[1], 1.0);
}

TEST(ransac, optimize) {
  MatX data;
  MatX x;
  struct ransac opt;

  // setup
  csv2mat(TEST_DATA, true, data);
  x = data.transpose();
  ransac_setup(&opt);
  ransac_configure(&opt, 40, 0.5, 5);

  // test and assert
  clock_t begin = clock();
  ransac_optimize(&opt, x);
  clock_t end = clock();

  double secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "elasped: " << secs << " seconds" << std::endl;

  ASSERT_TRUE(opt.model_params[0] < 23);
  ASSERT_TRUE(opt.model_params[0] > 18);
  ASSERT_TRUE(opt.model_params[1] < 13);
  ASSERT_TRUE(opt.model_params[1] > 8);
}

}  // end of yarl namespace
