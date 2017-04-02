#include "yarl/test.hpp"
#include "yarl/optimization/gp/gpdata.hpp"

#define TEST_DATA "./tests/data/optimization/gp/sine.csv"


namespace yarl {

TEST(GPData, load) {
  int retval;
  GPData data;
  MatX mat;
  std::vector<std::string> fields;

  csv2mat(TEST_DATA, true, mat);
  csvheader(TEST_DATA, fields);
  retval = data.load(mat, fields);
  ASSERT_EQ(0, retval);
  ASSERT_EQ(19, data.rows);
  ASSERT_EQ(2, data.cols);
  ASSERT_EQ(2, (int) data.fields.size());

  retval = data.load(TEST_DATA);
  ASSERT_EQ(0, retval);
  ASSERT_EQ(19, data.rows);
  ASSERT_EQ(2, data.cols);
  ASSERT_EQ(2, (int) data.fields.size());
}

TEST(GPData, fieldIndex) {
  int index;
  GPData data;

  data.load(TEST_DATA);

  index = data.fieldIndex("x");
  ASSERT_EQ(0, index);

  index = data.fieldIndex("y");
  ASSERT_EQ(1, index);

  index = data.fieldIndex("z");
  ASSERT_EQ(-1, index);
}

}  // end of yarl namespace
