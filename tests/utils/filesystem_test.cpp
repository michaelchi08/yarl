#include "yarl/yarl_test.hpp"
#include "yarl/utils/filesystem.hpp"

namespace yarl {

TEST(Utils, file_exists) {
  ASSERT_TRUE(file_exists("tests/data/utils/config.yaml"));
  ASSERT_FALSE(file_exists("tests/data/utils/bogus.yaml"));
}

TEST(Utils, path_split) {
  std::vector<std::string> splits;

  splits = path_split("/a/b/c.yaml");
  ASSERT_EQ(3, splits.size());
  ASSERT_EQ("a", splits[0]);
  ASSERT_EQ("b", splits[1]);
  ASSERT_EQ("c.yaml", splits[2]);
}

TEST(Utils, paths_combine) {
  std::string out;

  paths_combine("/a/b/c", "../", out);
  std::cout << out << std::endl;
  ASSERT_EQ("/a/b", out);

  paths_combine("/a/b/c", "../..", out);
  std::cout << out << std::endl;
  ASSERT_EQ("/a", out);

  paths_combine("/a/b/c", "d/e", out);
  std::cout << out << std::endl;
  ASSERT_EQ("/a/b/c/d/e", out);

  paths_combine("./a/b/c", "../d/e", out);
  std::cout << out << std::endl;
  ASSERT_EQ("./a/b/d/e", out);
}

}  // end of namespace
