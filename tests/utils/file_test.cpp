#include "yarl/test.hpp"
#include "yarl/utils/file.hpp"

namespace yarl {

TEST(Utils, file_exists) {
  EXPECT_TRUE(file_exists("tests/data/utils/config.yaml"));
  EXPECT_FALSE(file_exists("tests/data/utils/bogus.yaml"));
}

TEST(Utils, path_split) {
  std::vector<std::string> splits;

  splits = path_split("/a/b/c.yaml");
  EXPECT_EQ(3, (int) splits.size());
  EXPECT_EQ("a", splits[0]);
  EXPECT_EQ("b", splits[1]);
  EXPECT_EQ("c.yaml", splits[2]);
}

TEST(Utils, paths_combine) {
  std::string out;

  paths_combine("/a/b/c", "../", out);
  std::cout << out << std::endl;
  EXPECT_EQ("/a/b", out);

  paths_combine("/a/b/c", "../..", out);
  std::cout << out << std::endl;
  EXPECT_EQ("/a", out);

  paths_combine("/a/b/c", "d/e", out);
  std::cout << out << std::endl;
  EXPECT_EQ("/a/b/c/d/e", out);

  paths_combine("./a/b/c", "../d/e", out);
  std::cout << out << std::endl;
  EXPECT_EQ("./a/b/d/e", out);
}

}  // end of namespace
