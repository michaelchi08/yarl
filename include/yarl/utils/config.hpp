#ifndef UTILS_CONFIG_HPP
#define UTILS_CONFIG_HPP

#include <type_traits>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <libxml/parser.h>
#include <libxml/xpath.h>

#include "yarl/utils/file.hpp"
#include "yarl/utils/log.hpp"
#include "yarl/utils/math.hpp"

namespace yarl {

#define EXPATHCTX -1
#define EXPATHINV -2
#define EXPATHRES -3
#define ECONVTYPE -4
#define EPARAMNAN -5

enum ConfigDataType {
  TYPE_NOT_SET = 0,
  // PRIMITIVES
  BOOL = 1,
  INT = 2,
  FLOAT = 3,
  DOUBLE = 4,
  STRING = 5,
  // ARRAY
  BOOL_ARRAY = 11,
  INT_ARRAY = 12,
  FLOAT_ARRAY = 13,
  DOUBLE_ARRAY = 14,
  STRING_ARRAY = 15,
  // VECTOR
  VEC2 = 21,
  VEC3 = 22,
  VEC4 = 23,
  VECX = 24,
  // MATRIX
  MAT2 = 31,
  MAT3 = 32,
  MAT4 = 33,
  MATX = 34,
  CVMAT = 35
};

class ConfigParam {
public:
  enum ConfigDataType type;
  std::string key;
  void *data;
  bool optional;

  ConfigParam(void) {
    this->type = TYPE_NOT_SET;
    this->key = "";
    this->data = NULL;
    this->optional = false;
  }
};

#define CONFIG_PARSER_ADD_PARAM(TYPE, OUTVAR, OPTIONAL) \
  ConfigParam param;                                    \
  param.key = key;                                      \
  param.type = TYPE;                                    \
  param.data = out;                                     \
  param.optional = OPTIONAL;                            \
  this->params.push_back(param);

class ConfigParser {
public:
  bool config_loaded;
  std::vector<ConfigParam> params;
  xmlDocPtr doc;
  xmlXPathObjectPtr obj;

  ConfigParser(void);
  ~ConfigParser(void);
  // clang-format off
  void addParam(std::string key, bool *out, bool optional = false);
  void addParam(std::string key, int *out, bool optional = false);
  void addParam(std::string key, float *out, bool optional = false);
  void addParam(std::string key, double *out, bool optional = false);
  void addParam(std::string key, std::string *out, bool optional = false);
  void addParam(std::string key, std::vector<bool> *out, bool optional = false);
  void addParam(std::string key, std::vector<int> *out, bool optional = false);
  void addParam(std::string key, std::vector<float> *out, bool optional = false);
  void addParam(std::string key, std::vector<double> *out, bool optional = false);
  void addParam(std::string key, std::vector<std::string> *out, bool optional = false);
  void addParam(std::string key, Vec2 *out, bool optional = false);
  void addParam(std::string key, Vec3 *out, bool optional = false);
  void addParam(std::string key, Vec4 *out, bool optional = false);
  void addParam(std::string key, VecX *out, bool optional = false);
  void addParam(std::string key, Mat2 *out, bool optional = false);
  void addParam(std::string key, Mat3 *out, bool optional = false);
  void addParam(std::string key, Mat4 *out, bool optional = false);
  void addParam(std::string key, MatX *out, bool optional = false);
  void addParam(std::string key, cv::Mat *out, bool optional = false);
  // clang-format on
  int getParamPointer(std::string key);
  int getPrimitive(int type, void *out);
  int checkVector(std::string key, enum ConfigDataType type, bool optional);
  // int checkMatrix(const std::string key, const bool optional);
  // int loadPrimitive(const ConfigParam param);
  // int loadArray(const ConfigParam param);
  // int loadVector(const ConfigParam param);
  // int loadMatrix(const ConfigParam param);
  int load(const std::string config_file);
};

}  // end of yarl namespace
#endif
