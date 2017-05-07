#ifndef YARL_UTILS_CONFIG_HPP
#define YARL_UTILS_CONFIG_HPP

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
#include "yarl/utils/string.hpp"

namespace yarl {

#define EXPATHCTX -1
#define EXPATHINV -2
#define EXPATHRES -3
#define ECONVTYPE -4
#define EPARAMNAN -5
#define EVECINVSZ -6
#define EMATINVSZ -7
#define EINVBOOLD -8
#define ENOTVALUE -9
#define EMULVALUE -10

/**
 * Data type of config parameter
 */
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

  ConfigParam() {
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

  ConfigParser() : config_loaded(false), params(), doc(NULL), obj(NULL) {}

  ~ConfigParser() {
    if (this->obj) {
      xmlXPathFreeObject(this->obj);
    }

    if (this->config_loaded) {
      xmlFreeDoc(this->doc);
    }
  }

  // clang-format off
  void addParam(const std::string &key, bool *out, bool optional = false);
  void addParam(const std::string &key, int *out, bool optional = false);
  void addParam(const std::string &key, float *out, bool optional = false);
  void addParam(const std::string &key, double *out, bool optional = false);
  void addParam(const std::string &key, std::string *out, bool optional = false);
  void addParam(const std::string &key, std::vector<bool> *out, bool optional = false);
  void addParam(const std::string &key, std::vector<int> *out, bool optional = false);
  void addParam(const std::string &key, std::vector<float> *out, bool optional = false);
  void addParam(const std::string &key, std::vector<double> *out, bool optional = false);
  void addParam(const std::string &key, std::vector<std::string> *out, bool optional = false);
  void addParam(const std::string &key, Vec2 *out, bool optional = false);
  void addParam(const std::string &key, Vec3 *out, bool optional = false);
  void addParam(const std::string &key, Vec4 *out, bool optional = false);
  void addParam(const std::string &key, VecX *out, bool optional = false);
  void addParam(const std::string &key, Mat2 *out, bool optional = false);
  void addParam(const std::string &key, Mat3 *out, bool optional = false);
  void addParam(const std::string &key, Mat4 *out, bool optional = false);
  void addParam(const std::string &key, MatX *out, bool optional = false);
  void addParam(const std::string &key, cv::Mat *out, bool optional = false);
  // clang-format on
  int setXMLPointer(const std::string &key);
  void resetXMLPointer();
  int getXMLValue(const std::string &key, std::string &value);
  int getXMLValues(const std::string &key, std::vector<std::string> &values);
  int checkVector(const std::string &key, enum ConfigDataType type);
  int checkMatrix(const std::string &key, enum ConfigDataType type);
  int parsePrimitive(const std::string &key,
                     enum ConfigDataType type,
                     void *out);
  int parseArray(const std::string &key, enum ConfigDataType type, void *out);
  int parseVector(const std::string &key,
                  enum ConfigDataType type,
                  void *out);
  int parseMatrix(const std::string &key,
                  enum ConfigDataType type,
                  void *out);
  int parsePrimitive(ConfigParam &param);
  int parseArray(ConfigParam &param);
  int parseVector(ConfigParam &param);
  int parseMatrix(ConfigParam &param);
  int load(const std::string &config_file);
};

}  // end of yarl namespace
#endif
