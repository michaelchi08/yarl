#include "yarl/test.hpp"
#include "yarl/optimization/gp/data.hpp"

#define TEST_DATA "./tests/data/optimization/gp/sine.csv"

namespace yarl {
namespace gp {

TEST(Data, load) {
  int retval;
  Data data;
  MatX mat;
  std::vector<std::string> fields;

  csv2mat(TEST_DATA, true, mat);
  csvheader(TEST_DATA, fields);
  retval = data.load(mat, fields);
  EXPECT_EQ(0, retval);
  EXPECT_EQ(19, data.rows);
  EXPECT_EQ(2, data.cols);
  EXPECT_EQ(2, (int) data.fields.size());

  retval = data.load(TEST_DATA);
  EXPECT_EQ(0, retval);
  EXPECT_EQ(19, data.rows);
  EXPECT_EQ(2, data.cols);
  EXPECT_EQ(2, (int) data.fields.size());
}

TEST(Data, fieldIndex) {
  int index;
  Data data;

  data.load(TEST_DATA);

  index = data.fieldIndex("x");
  EXPECT_EQ(0, index);

  index = data.fieldIndex("y");
  EXPECT_EQ(1, index);

  index = data.fieldIndex("z");
  EXPECT_EQ(-1, index);
}

}  // end of gp namespace
}  // end of yarl namespace
