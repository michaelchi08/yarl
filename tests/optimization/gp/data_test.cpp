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

TEST(Data, fieldIndex) {
  int index;
  Data data;

  data.load(TEST_DATA);

  index = data.fieldIndex("x");
  ASSERT_EQ(0, index);

  index = data.fieldIndex("y");
  ASSERT_EQ(1, index);

  index = data.fieldIndex("z");
  ASSERT_EQ(-1, index);
}

}  // end of gp namespace
}  // end of yarl namespace
