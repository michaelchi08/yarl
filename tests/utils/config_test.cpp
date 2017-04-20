#include "yarl/test.hpp"
#include "yarl/utils/config.hpp"
#include "yarl/utils/data.hpp"

#define TEST_CONFIG "tests/data/utils/config.xml"

namespace yarl {

TEST(ConfigParam, constructor) {
  ConfigParam param;

  EXPECT_EQ(TYPE_NOT_SET, param.type);
  EXPECT_EQ("", param.key);
  EXPECT_EQ(NULL, param.data);
  EXPECT_FALSE(param.optional);
}

TEST(ConfigParser, constructor) {
  ConfigParser parser;
}

TEST(ConfigParser, addParam) {
  bool b;
  int i;
  float f;
  double d;
  std::string s;

  std::vector<bool> b_array;
  std::vector<int> i_array;
  std::vector<float> f_array;
  std::vector<double> d_array;
  std::vector<std::string> s_array;

  Vec2 vec2;
  Vec3 vec3;
  Vec4 vec4;
  VecX vecx;

  Mat2 mat2;
  Mat3 mat3;
  Mat4 mat4;
  MatX matx;
  cv::Mat cvmat;

  ConfigParser parser;

  parser.addParam("bool", &b);
  parser.addParam("int", &i);
  parser.addParam("float", &f);
  parser.addParam("double", &d);
  parser.addParam("string", &s);

  parser.addParam("bool_array", &b_array);
  parser.addParam("int_array", &i_array);
  parser.addParam("float_array", &f_array);
  parser.addParam("double_array", &d_array);
  parser.addParam("string_array", &s_array);

  parser.addParam("vector2", &vec2);
  parser.addParam("vector3", &vec3);
  parser.addParam("vector4", &vec4);
  parser.addParam("vector", &vecx);

  parser.addParam("matrix2", &mat2);
  parser.addParam("matrix3", &mat3);
  parser.addParam("matrix4", &mat4);
  parser.addParam("matrix", &matx);
  parser.addParam("matrix", &cvmat);

  EXPECT_EQ(19, (int) parser.params.size());
  EXPECT_EQ(BOOL, parser.params[0].type);
  EXPECT_EQ("bool", parser.params[0].key);
  EXPECT_TRUE(parser.params[0].data != NULL);
}

TEST(ConfigParser, setXMLPointer) {
  ConfigParser parser;
  int retval;

  // setup
  parser.load(TEST_CONFIG);

  // test xpath
  retval = parser.setXMLPointer("/config/int");
  EXPECT_EQ(0, retval);
  EXPECT_EQ(1, parser.obj->type);

  // test bad xpath
  retval = parser.setXMLPointer("#");
  EXPECT_EQ(EXPATHINV, retval);
  EXPECT_EQ(NULL, parser.obj);

  // test no results
  retval = parser.setXMLPointer("/config/bogus");
  EXPECT_EQ(EXPATHRES, retval);
  EXPECT_EQ(NULL, parser.obj);
}

TEST(ConfigParser, getXMLValue) {
  int retval;
  ConfigParser parser;
  std::string value;

  // setup
  parser.load(TEST_CONFIG);

  // test
  retval = parser.getXMLValue("/config/int", value);
  EXPECT_EQ(0, retval);
  EXPECT_EQ("1", value);
}

TEST(ConfigParser, getXMLValues) {
  int retval;
  ConfigParser parser;
  std::vector<std::string> values;

  // setup
  parser.load(TEST_CONFIG);

  // test
  retval = parser.getXMLValues("/config/int_array/item", values);
  EXPECT_EQ(0, retval);
  EXPECT_EQ(4, (int) values.size());
  EXPECT_EQ("0", values[0]);
}

TEST(ConfigParser, checkVector) {
  ConfigParser parser;
  int retval;

  // setup
  parser.load(TEST_CONFIG);

  retval = parser.checkVector("/config/vector2", VEC2);
  EXPECT_EQ(0, retval);

  retval = parser.checkVector("/config/vector3", VEC3);
  EXPECT_EQ(0, retval);

  retval = parser.checkVector("/config/vector4", VEC4);
  EXPECT_EQ(0, retval);

  retval = parser.checkVector("/config/vectorX", VECX);
  EXPECT_EQ(0, retval);

  retval = parser.checkVector("/config/vectorX", VEC2);
  EXPECT_EQ(EVECINVSZ, retval);
}

TEST(ConfigParser, checkMatrix) {
  ConfigParser parser;
  int retval;

  // setup
  parser.load(TEST_CONFIG);

  retval = parser.checkMatrix("/config/matrix2", MAT2);
  EXPECT_EQ(0, retval);

  retval = parser.checkMatrix("/config/matrix3", MAT3);
  EXPECT_EQ(0, retval);

  retval = parser.checkMatrix("/config/matrix4", MAT4);
  EXPECT_EQ(0, retval);

  retval = parser.checkMatrix("/config/matrixX", MATX);
  EXPECT_EQ(0, retval);

  retval = parser.checkMatrix("/config/matrix4", MATX);
  EXPECT_EQ(0, retval);
}

TEST(ConfigParser, parsePrimitive) {
  ConfigParser parser;
  int i;
  float f;
  double d;
  std::string s;
  ConfigParam param;

  // setup
  i = 0;
  f = 0;
  d = 0;
  s = "";
  parser.load(TEST_CONFIG);

  // INTEGER
  param.optional = false;
  param.type = INT;
  param.key = "/config/int";
  param.data = &i;
  parser.parsePrimitive(param);
  EXPECT_EQ(1, i);

  // FLOAT
  param.optional = false;
  param.type = FLOAT;
  param.key = "/config/float";
  param.data = &f;
  parser.parsePrimitive(param);
  EXPECT_FLOAT_EQ(1.0, f);

  // DOUBLE
  param.optional = false;
  param.type = DOUBLE;
  param.key = "/config/double";
  param.data = &d;
  parser.parsePrimitive(param);
  EXPECT_FLOAT_EQ(1.0, d);

  // STRING
  param.optional = false;
  param.type = STRING;
  param.key = "/config/string";
  param.data = &s;
  parser.parsePrimitive(param);
  EXPECT_EQ("Hello World", s);
}

TEST(ConfigParser, parseArray) {
  std::vector<bool> b_array;
  std::vector<int> i_array;
  std::vector<float> f_array;
  std::vector<double> d_array;
  std::vector<std::string> s_array;
  ConfigParser parser;
  ConfigParam param;

  // setup
  parser.load(TEST_CONFIG);

  // INTEGER
  param.optional = false;
  param.type = INT_ARRAY;
  param.key = "/config/int_array";
  param.data = &i_array;
  parser.parseArray(param.key, param.type, param.data);

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(i, i_array[i]);
  }

  // FLOAT
  param.optional = false;
  param.type = FLOAT_ARRAY;
  param.key = "/config/float_array";
  param.data = &f_array;
  parser.parseArray(param.key, param.type, param.data);

  for (int i = 0; i < 4; i++) {
    EXPECT_FLOAT_EQ((float) i, f_array[i]);
  }

  // DOUBLE
  param.optional = false;
  param.type = DOUBLE_ARRAY;
  param.key = "/config/double_array";
  param.data = &d_array;
  parser.parseArray(param.key, param.type, param.data);

  for (int i = 0; i < 4; i++) {
    EXPECT_FLOAT_EQ((double) i, d_array[i]);
  }

  // STRING
  param.optional = false;
  param.type = STRING_ARRAY;
  param.key = "/config/string_array";
  param.data = &s_array;
  parser.parseArray(param.key, param.type, param.data);

  EXPECT_EQ("A", s_array[0]);
  EXPECT_EQ("B", s_array[1]);
  EXPECT_EQ("C", s_array[2]);
  EXPECT_EQ("D", s_array[3]);
}

TEST(ConfigParser, parseVector) {
  Vec2 vec2;
  Vec3 vec3;
  Vec4 vec4;
  VecX vecx;
  ConfigParser parser;
  ConfigParam param;

  // setup
  parser.load(TEST_CONFIG);

  // VECTOR 2
  param.optional = false;
  param.type = VEC2;
  param.key = "/config/vector2";
  param.data = &vec2;
  parser.parseVector(param.key, param.type, param.data);

  EXPECT_FLOAT_EQ(1.0, vec2(0));
  EXPECT_FLOAT_EQ(2.0, vec2(1));

  // VECTOR 3
  param.optional = false;
  param.type = VEC3;
  param.key = "/config/vector3";
  param.data = &vec3;
  parser.parseVector(param.key, param.type, param.data);

  EXPECT_FLOAT_EQ(1.0, vec3(0));
  EXPECT_FLOAT_EQ(2.0, vec3(1));
  EXPECT_FLOAT_EQ(3.0, vec3(2));

  // VECTOR 4
  param.optional = false;
  param.type = VEC4;
  param.key = "/config/vector4";
  param.data = &vec4;
  parser.parseVector(param.key, param.type, param.data);

  EXPECT_FLOAT_EQ(1.0, vec4(0));
  EXPECT_FLOAT_EQ(2.0, vec4(1));
  EXPECT_FLOAT_EQ(3.0, vec4(2));
  EXPECT_FLOAT_EQ(4.0, vec4(3));

  // VECTOR X
  param.optional = false;
  param.type = VECX;
  param.key = "/config/vectorX";
  param.data = &vecx;
  parser.parseVector(param.key, param.type, param.data);

  for (int i = 0; i < 5; i++) {
    EXPECT_FLOAT_EQ(i + 1, vecx(i));
  }
}

TEST(ConfigParser, parseMatrix) {
  int index;
  Mat2 mat2;
  Mat3 mat3;
  Mat4 mat4;
  MatX matx;
  cv::Mat cvmat;
  ConfigParser parser;
  ConfigParam param;

  // setup
  parser.load(TEST_CONFIG);

  // MATRIX 2
  param.optional = false;
  param.type = MAT2;
  param.key = "/config/matrix2";
  param.data = &mat2;
  parser.parseMatrix(param);

  EXPECT_FLOAT_EQ(1.0, mat2(0, 0));
  EXPECT_FLOAT_EQ(2.0, mat2(0, 1));
  EXPECT_FLOAT_EQ(3.0, mat2(1, 0));
  EXPECT_FLOAT_EQ(4.0, mat2(1, 1));

  // MATRIX 3
  param.optional = false;
  param.type = MAT3;
  param.key = "/config/matrix3";
  param.data = &mat3;
  parser.parseMatrix(param);

  index = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(index + 1.0, mat3(i, j));
      index++;
    }
  }

  // MATRIX 4
  param.optional = false;
  param.type = MAT4;
  param.key = "/config/matrix4";
  param.data = &mat4;
  parser.parseMatrix(param);

  index = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_FLOAT_EQ(index + 1.0, mat4(i, j));
      index++;
    }
  }

  // MATRIX X
  param.optional = false;
  param.type = MATX;
  param.key = "/config/matrixX";
  param.data = &matx;
  parser.parseMatrix(param);

  index = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      EXPECT_FLOAT_EQ(index + 1.0, matx(i, j));
      index++;
    }
  }

  // CV MATRIX
  param.optional = false;
  param.type = CVMAT;
  param.key = "/config/matrixX";
  param.data = &cvmat;
  parser.parseMatrix(param);

  index = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      EXPECT_FLOAT_EQ(index + 1.0, cvmat.at<double>(i, j));
      index++;
    }
  }
}

TEST(ConfigParser, load) {
  int retval;
  bool b;
  int i;
  float f;
  double d;
  std::string s;

  std::vector<bool> b_array;
  std::vector<int> i_array;
  std::vector<float> f_array;
  std::vector<double> d_array;
  std::vector<std::string> s_array;

  Vec2 vec2;
  Vec3 vec3;
  Vec4 vec4;
  VecX vecx;

  Mat2 mat2;
  Mat3 mat3;
  Mat4 mat4;
  MatX matx;
  cv::Mat cvmat;

  ConfigParser parser;

  parser.addParam("/config/bool", &b);
  parser.addParam("/config/int", &i);
  parser.addParam("/config/float", &f);
  parser.addParam("/config/double", &d);
  parser.addParam("/config/string", &s);

  parser.addParam("/config/bool_array", &b_array);
  parser.addParam("/config/int_array", &i_array);
  parser.addParam("/config/float_array", &f_array);
  parser.addParam("/config/double_array", &d_array);
  parser.addParam("/config/string_array", &s_array);

  parser.addParam("/config/vector2", &vec2);
  parser.addParam("/config/vector3", &vec3);
  parser.addParam("/config/vector4", &vec4);
  parser.addParam("/config/vectorX", &vecx);

  parser.addParam("/config/matrix2", &mat2);
  parser.addParam("/config/matrix3", &mat3);
  parser.addParam("/config/matrix4", &mat4);
  parser.addParam("/config/matrixX", &matx);
  parser.addParam("/config/matrixX", &cvmat);

  retval = parser.load(TEST_CONFIG);
  if (retval != 0) {
    FAIL();
  }

  std::cout << "bool: " << b << std::endl;
  std::cout << "int: " << i << std::endl;
  std::cout << "float: " << f << std::endl;
  std::cout << "double: " << d << std::endl;
  std::cout << "string: " << s << std::endl;
  std::cout << std::endl;

  std::cout << "bool_array: " << std::endl;
  for (size_t i = 0; i < b_array.size(); i++) {
    std::cout << b_array[i] << std::endl;
  }
  std::cout << std::endl;

  std::cout << "vector2: " << vec2.transpose() << std::endl;
  std::cout << "vector3: " << vec3.transpose() << std::endl;
  std::cout << "vector4: " << vec4.transpose() << std::endl;
  std::cout << "vector: " << vecx.transpose() << std::endl;
  std::cout << std::endl;

  std::cout << "matrix2: \n" << mat2 << std::endl;
  std::cout << "matrix3: \n" << mat3 << std::endl;
  std::cout << "matrix4: \n" << mat4 << std::endl;
  std::cout << "matrix: \n" << matx << std::endl;
  std::cout << "cvmatrix: \n" << cvmat << std::endl;
  std::cout << std::endl;
}

}  // end of  yarl namespace
