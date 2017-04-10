#include "yarl/test.hpp"
#include "yarl/vision/dataset.hpp"

#define TEST_CONFIG "tests/data/vision/dataset/vo_test.xml"
#define TEST_OUTPUT "/tmp/dataset_test.csv"

namespace yarl {

TEST(TestDataset, constructor) {
  TestDataset dataset;

  ASSERT_EQ(-1, dataset.image_width);
  ASSERT_EQ(-1, dataset.image_height);
}

TEST(TestDataset, configure) {
  TestDataset dataset;
  int retval;

  retval = dataset.configure(TEST_CONFIG);
  ASSERT_EQ(0, retval);
  ASSERT_EQ(640, dataset.image_width);
  ASSERT_EQ(640, dataset.image_height);
  ASSERT_FLOAT_EQ(554.38, dataset.K(0, 0));
  ASSERT_FLOAT_EQ(554.38, dataset.K(1, 1));
  ASSERT_FLOAT_EQ(0.0, dataset.K(2, 0));
  ASSERT_FLOAT_EQ(0.0, dataset.K(2, 1));
}

TEST(TestDataset, generateTestData) {
  TestDataset dataset;
  int retval;

  dataset.configure(TEST_CONFIG);
  retval = dataset.generateTestData(TEST_OUTPUT);

  ASSERT_EQ(0, retval);
}

}  // end of yarl namespace
