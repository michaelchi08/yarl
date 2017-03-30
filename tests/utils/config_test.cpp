#include "yarl/yarl_test.hpp"
#include "yarl/utils/config.hpp"
#include "yarl/utils/data.hpp"

#define TEST_CONFIG "tests/data/utils/config.xml"

namespace yarl {

TEST(ConfigParam, constructor) {
  ConfigParam param;

  ASSERT_EQ(TYPE_NOT_SET, param.type);
  ASSERT_EQ("", param.key);
  ASSERT_EQ(NULL, param.data);
  ASSERT_EQ(false, param.optional);
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

  ASSERT_EQ(19, parser.params.size());
  ASSERT_EQ(BOOL, parser.params[0].type);
  ASSERT_EQ("bool", parser.params[0].key);
  ASSERT_TRUE(parser.params[0].data != NULL);
}

TEST(ConfigParser, getParamPointer) {
  ConfigParser parser;
  int retval;

  // setup
  parser.load(TEST_CONFIG);

  // test xpath
  retval = parser.getParamPointer("/config/int");
  ASSERT_EQ(0, retval);
  ASSERT_EQ(1, parser.obj->type);

  // test bad xpath
  retval = parser.getParamPointer("#");
  ASSERT_EQ(EXPATHINV, retval);
  ASSERT_EQ(NULL, parser.obj);

  // test no results
  retval = parser.getParamPointer("/bogus");
  ASSERT_EQ(EXPATHRES, retval);
  ASSERT_EQ(NULL, parser.obj);
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
  ASSERT_EQ(1, i);

  // FLOAT
  param.optional = false;
  param.type = FLOAT;
  param.key = "/config/float";
  param.data = &f;
  parser.parsePrimitive(param);
  ASSERT_FLOAT_EQ(1.0, f);

  // DOUBLE
  param.optional = false;
  param.type = DOUBLE;
  param.key = "/config/double";
  param.data = &d;
  parser.parsePrimitive(param);
  ASSERT_FLOAT_EQ(1.0, d);

  // STRING
  param.optional = false;
  param.type = STRING;
  param.key = "/config/string";
  param.data = &s;
  parser.parsePrimitive(param);
  ASSERT_EQ("Hello World", s);
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
    ASSERT_EQ(i, i_array[i]);
  }

  // FLOAT
  param.optional = false;
  param.type = FLOAT_ARRAY;
  param.key = "/config/float_array";
  param.data = &f_array;
  parser.parseArray(param.key, param.type, param.data);

  for (int i = 0; i < 4; i++) {
    ASSERT_FLOAT_EQ((float) i, f_array[i]);
  }

  // DOUBLE
  param.optional = false;
  param.type = DOUBLE_ARRAY;
  param.key = "/config/double_array";
  param.data = &d_array;
  parser.parseArray(param.key, param.type, param.data);

  for (int i = 0; i < 4; i++) {
    ASSERT_FLOAT_EQ((double) i, d_array[i]);
  }

  // STRING
  param.optional = false;
  param.type = STRING_ARRAY;
  param.key = "/config/string_array";
  param.data = &s_array;
  parser.parseArray(param.key, param.type, param.data);

  ASSERT_EQ("A", s_array[0]);
  ASSERT_EQ("B", s_array[1]);
  ASSERT_EQ("C", s_array[2]);
  ASSERT_EQ("D", s_array[3]);
}

// TEST(ConfigParser, loadVector) {
//   Vec2 vec2;
//   Vec3 vec3;
//   Vec4 vec4;
//   VecX vecx;
//   ConfigParser parser;
//   ConfigParam param;
//
//   // setup
//   parser.load(TEST_CONFIG);
//
//   // VECTOR 2
//   param.optional = false;
//   param.type = VEC2;
//   param.key = "vector2";
//   param.vec2 = &vec2;
//   parser.loadVector(param);
//
//   ASSERT_FLOAT_EQ(1.0, vec2(0));
//   ASSERT_FLOAT_EQ(2.0, vec2(1));
//
//   // VECTOR 3
//   param.optional = false;
//   param.type = VEC3;
//   param.key = "vector3";
//   param.vec3 = &vec3;
//   parser.loadVector(param);
//
//   ASSERT_FLOAT_EQ(1.0, vec3(0));
//   ASSERT_FLOAT_EQ(2.0, vec3(1));
//   ASSERT_FLOAT_EQ(3.0, vec3(2));
//
//   // VECTOR 4
//   param.optional = false;
//   param.type = VEC4;
//   param.key = "vector4";
//   param.vec4 = &vec4;
//   parser.loadVector(param);
//
//   ASSERT_FLOAT_EQ(1.0, vec4(0));
//   ASSERT_FLOAT_EQ(2.0, vec4(1));
//   ASSERT_FLOAT_EQ(3.0, vec4(2));
//   ASSERT_FLOAT_EQ(4.0, vec4(3));
//
//   // VECTOR X
//   param.optional = false;
//   param.type = VECX;
//   param.key = "vector";
//   param.vecx = &vecx;
//   parser.loadVector(param);
//
//   for (int i = 0; i < 10; i++) {
//     ASSERT_FLOAT_EQ((double) i + 1.0, vecx(i));
//   }
// }

// TEST(ConfigParser, loadMatrix) {
//   int index;
//   Mat2 mat2;
//   Mat3 mat3;
//   Mat4 mat4;
//   MatX matx;
//   cv::Mat cvmat;
//   ConfigParser parser;
//   ConfigParam param;
//
//   // setup
//   parser.root = YAML::LoadFile(TEST_CONFIG);
//
//   // MATRIX 2
//   param.optional = false;
//   param.type = MAT2;
//   param.key = "matrix2";
//   param.mat2 = &mat2;
//   parser.loadMatrix(param);
//
//   ASSERT_FLOAT_EQ(1.0, mat2(0, 0));
//   ASSERT_FLOAT_EQ(2.0, mat2(0, 1));
//   ASSERT_FLOAT_EQ(3.0, mat2(1, 0));
//   ASSERT_FLOAT_EQ(4.0, mat2(1, 1));
//
//   // MATRIX 3
//   param.optional = false;
//   param.type = MAT3;
//   param.key = "matrix3";
//   param.mat3 = &mat3;
//   parser.loadMatrix(param);
//
//   index = 0;
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//       ASSERT_FLOAT_EQ(index + 1.0, mat3(i, j));
//       index++;
//     }
//   }
//
//   // MATRIX 4
//   param.optional = false;
//   param.type = MAT4;
//   param.key = "matrix4";
//   param.mat4 = &mat4;
//   parser.loadMatrix(param);
//
//   index = 0;
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       ASSERT_FLOAT_EQ(index + 1.0, mat4(i, j));
//       index++;
//     }
//   }
//
//   // MATRIX X
//   param.optional = false;
//   param.type = MATX;
//   param.key = "matrix";
//   param.matx = &matx;
//   parser.loadMatrix(param);
//
//   index = 0;
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 4; j++) {
//       ASSERT_FLOAT_EQ(index + 1.0, matx(i, j));
//       index++;
//     }
//   }
//
//   // CV MATRIX
//   param.optional = false;
//   param.type = CVMAT;
//   param.key = "matrix";
//   param.cvmat = &cvmat;
//   parser.loadMatrix(param);
//
//   index = 0;
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 4; j++) {
//       ASSERT_FLOAT_EQ(index + 1.0, cvmat.at<double>(i, j));
//       index++;
//     }
//   }
// }
//
// TEST(ConfigParser, load) {
//   int retval;
//   bool b;
//   int i;
//   float f;
//   double d;
//   std::string s;
//
//   std::vector<bool> b_array;
//   std::vector<int> i_array;
//   std::vector<float> f_array;
//   std::vector<double> d_array;
//   std::vector<std::string> s_array;
//
//   Vec2 vec2;
//   Vec3 vec3;
//   Vec4 vec4;
//   VecX vecx;
//
//   Mat2 mat2;
//   Mat3 mat3;
//   Mat4 mat4;
//   MatX matx;
//   cv::Mat cvmat;
//
//   ConfigParser parser;
//
//   parser.addParam<bool>("bool", &b);
//   parser.addParam<int>("int", &i);
//   parser.addParam<float>("float", &f);
//   parser.addParam<double>("double", &d);
//   parser.addParam<std::string>("string", &s);
//
//   parser.addParam<std::vector<bool>>("bool_array", &b_array);
//   parser.addParam<std::vector<int>>("int_array", &i_array);
//   parser.addParam<std::vector<float>>("float_array", &f_array);
//   parser.addParam<std::vector<double>>("double_array", &d_array);
//   parser.addParam<std::vector<std::string>>("string_array", &s_array);
//
//   parser.addParam<Vec2>("vector2", &vec2);
//   parser.addParam<Vec3>("vector3", &vec3);
//   parser.addParam<Vec4>("vector4", &vec4);
//   parser.addParam<VecX>("vector", &vecx);
//
//   parser.addParam<Mat2>("matrix2", &mat2);
//   parser.addParam<Mat3>("matrix3", &mat3);
//   parser.addParam<Mat4>("matrix4", &mat4);
//   parser.addParam<MatX>("matrix", &matx);
//   parser.addParam<cv::Mat>("matrix", &cvmat);
//
//   retval = parser.load(TEST_CONFIG);
//   if (retval != 0) {
//     FAIL();
//   }
//
//   std::cout << "bool: " << b << std::endl;
//   std::cout << "int: " << i << std::endl;
//   std::cout << "float: " << f << std::endl;
//   std::cout << "double: " << d << std::endl;
//   std::cout << "string: " << s << std::endl;
//   std::cout << std::endl;
//
//   std::cout << "vector2: " << vec2.transpose() << std::endl;
//   std::cout << "vector3: " << vec3.transpose() << std::endl;
//   std::cout << "vector4: " << vec4.transpose() << std::endl;
//   std::cout << "vector: " << vecx.transpose() << std::endl;
//   std::cout << std::endl;
//
//   std::cout << "matrix2: \n" << mat2 << std::endl;
//   std::cout << "matrix3: \n" << mat3 << std::endl;
//   std::cout << "matrix4: \n" << mat4 << std::endl;
//   std::cout << "matrix: \n" << matx << std::endl;
//   std::cout << "cvmatrix: \n" << cvmat << std::endl;
//   std::cout << std::endl;
// }

}  // end of  yarl namespace
