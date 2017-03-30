#include "yarl/utils/config.hpp"

namespace yarl {

ConfigParser::ConfigParser(void) {
  this->config_loaded = false;
  this->doc = NULL;
  this->obj = NULL;
}

ConfigParser::~ConfigParser(void) {
  if (this->obj) {
    xmlXPathFreeObject(this->obj);
  }

  if (this->config_loaded) {
    xmlFreeDoc(this->doc);
  }
}

// clang-format off
void ConfigParser::addParam(std::string key, bool *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(BOOL, out, optional);
}

void ConfigParser::addParam(std::string key, int *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(INT, out, optional);
}

void ConfigParser::addParam(std::string key, float *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(FLOAT, out, optional);
}

void ConfigParser::addParam(std::string key, double *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(DOUBLE, out, optional);
}

void ConfigParser::addParam(std::string key, std::string *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(STRING, out, optional);
}

void ConfigParser::addParam(std::string key, std::vector<bool> *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(BOOL_ARRAY, out, optional);
}

void ConfigParser::addParam(std::string key, std::vector<int> *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(INT_ARRAY, out, optional);
}

void ConfigParser::addParam(std::string key, std::vector<float> *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(FLOAT_ARRAY, out, optional);
}

void ConfigParser::addParam(std::string key, std::vector<double> *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(DOUBLE_ARRAY, out, optional);
}

void ConfigParser::addParam(std::string key, std::vector<std::string> *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(STRING_ARRAY, out, optional);
}

void ConfigParser::addParam(std::string key, Vec2 *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(VEC2, out, optional);
}

void ConfigParser::addParam(std::string key, Vec3 *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(VEC3, out, optional);
}

void ConfigParser::addParam(std::string key, Vec4 *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(VEC4, out, optional);
}

void ConfigParser::addParam(std::string key, VecX *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(VECX, out, optional);
}

void ConfigParser::addParam(std::string key, Mat2 *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(MAT2, out, optional);
}

void ConfigParser::addParam(std::string key, Mat3 *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(MAT3, out, optional);
}

void ConfigParser::addParam(std::string key, Mat4 *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(MAT4, out, optional);
}

void ConfigParser::addParam(std::string key, MatX *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(MATX, out, optional);
}

void ConfigParser::addParam(std::string key, cv::Mat *out, bool optional) {
  CONFIG_PARSER_ADD_PARAM(CVMAT, out, optional);
}
// clang-format on

int ConfigParser::getParamPointer(std::string key) {
  xmlChar *xpath;
  xmlXPathContextPtr context;

  // create xpath context
  context = xmlXPathNewContext(this->doc);
  if (context == NULL) {
    log_err("Failed to create XPath context");
    xmlXPathFreeContext(context);
    return EXPATHCTX;
  }

  // free previous xpath object if set
  if (this->obj) {
    xmlXPathFreeObject(this->obj);
    this->obj = NULL;
  }

  // evaluate xpath context
  xpath =
    const_cast<xmlChar *>(reinterpret_cast<const xmlChar *>(key.c_str()));
  this->obj = xmlXPathEvalExpression(xpath, context);
  xmlXPathFreeContext(context);

  // check xpath results
  if (this->obj == NULL) {
    log_err("Invalid XPath [%s]", key.c_str());
    xmlXPathFreeObject(this->obj);
    this->obj = NULL;
    return EXPATHINV;

  } else if (xmlXPathNodeSetIsEmpty(this->obj->nodesetval)) {
    log_err("XPath [%s] not found!", key.c_str());
    xmlXPathFreeObject(this->obj);
    this->obj = NULL;
    return EXPATHRES;
  }

  return 0;
}

int ConfigParser::checkVector(std::string key, enum ConfigDataType type) {
  int retval;
  xmlNode *xml_node;
  xmlChar *xml_value;
  std::vector<std::string> data;

  // check key
  retval = this->getParamPointer(key + "/vec");
  if (retval != 0) {
    return retval;
  }

  // check data key
  retval = this->getParamPointer(key + "/vec");
  if (retval != 0) {
    return retval;
  }
  xml_node = this->obj->nodesetval->nodeTab[0];
  xml_value = xmlNodeListGetString(this->doc, xml_node->xmlChildrenNode, 1);
  std::string s = std::string(reinterpret_cast<char *>(xml_value));
  split(s, ',', data);

  // check number of values
  switch (type) {
  case VEC2:
    return (data.size() == 2) ? 0 : EVECINVSZ;
  case VEC3:
    return (data.size() == 3) ? 0 : EVECINVSZ;
  case VEC4:
    return (data.size() == 4) ? 0 : EVECINVSZ;
  case VECX:
    return 0;
  default:
    return ECONVTYPE;
  }

  return 0;
}

int ConfigParser::checkMatrix(std::string key, enum ConfigDataType type) {
  int retval, rows, cols;
  xmlNode *xml_node;
  xmlChar *xml_value;
  std::vector<std::string> data;

  // get rows and cols
  retval = this->parsePrimitive(key + "/rows", INT, &rows);
  if (retval != 0) {
    return retval;
  }

  retval = this->parsePrimitive(key + "/cols", INT, &cols);
  if (retval != 0) {
    return retval;
  }

  // check data key
  retval = this->getParamPointer(key + "/data");
  if (retval != 0) {
    return retval;
  }
  xml_node = this->obj->nodesetval->nodeTab[0];
  xml_value = xmlNodeListGetString(this->doc, xml_node->xmlChildrenNode, 1);
  std::string s = std::string(reinterpret_cast<char *>(xml_value));
  split(s, ',', data);

  // check number of values
  switch (type) {
  case MAT2:
    return (static_cast<int>(data.size()) == 4) ? 0 : EMATINVSZ;
  case MAT3:
    return (static_cast<int>(data.size()) == 9) ? 0 : EMATINVSZ;
  case MAT4:
    return (static_cast<int>(data.size()) == 16) ? 0 : EMATINVSZ;
  case MATX:
    return (static_cast<int>(data.size()) == (rows * cols)) ? 0 : EMATINVSZ;
  case CVMAT:
    return (static_cast<int>(data.size()) == (rows * cols)) ? 0 : EMATINVSZ;
  default:
    return ECONVTYPE;
  }

  return 0;
}

int ConfigParser::parsePrimitive(std::string key,
                                 enum ConfigDataType type,
                                 void *out) {
  int retval;
  xmlNode *xml_node;
  xmlChar *xml_value;
  char *value;

  // pre-check
  retval = this->getParamPointer(key);
  if (retval != 0) {
    return retval;
  }

  // get value
  xml_node = this->obj->nodesetval->nodeTab[0];
  xml_value = xmlNodeListGetString(this->doc, xml_node->xmlChildrenNode, 1);

  // convert value
  value = reinterpret_cast<char *>(xml_value);
  if (type == BOOL) {
    // strip white space in string
    std::string v = std::string(value);
    strip(v, ' ');

    // parse bool
    if (v.compare("true") == 0 || v.compare("1") == 0) {
      *reinterpret_cast<bool *>(out) = true;
    } else if (v.compare("false") == 0 || v.compare("0") == 0) {
      *reinterpret_cast<bool *>(out) = false;
    } else {
      return EINVBOOLD;
    }

  } else if (type == INT) {
    *reinterpret_cast<int *>(out) = atoi(value);

  } else if (type == FLOAT) {
    *reinterpret_cast<float *>(out) = static_cast<float>(atof(value));

  } else if (type == DOUBLE) {
    *reinterpret_cast<double *>(out) = atof(value);

  } else if (type == STRING) {
    *reinterpret_cast<std::string *>(out) = strim(std::string(value));

  } else {
    return ECONVTYPE;
  }

  // clean up
  xmlFree(xml_value);
  xmlXPathFreeObject(this->obj);
  this->obj = NULL;

  return 0;
}

int ConfigParser::parseArray(std::string key,
                             enum ConfigDataType type,
                             void *out) {
  int retval;
  char *value;
  int i;
  float f;
  double d;
  std::string s;
  xmlNode *xml_node;
  xmlChar *xml_value;

  // pre-check
  retval = this->getParamPointer(key + "/item");
  if (retval != 0) {
    return retval;
  }

  // parse array
  for (int x = 0; x < this->obj->nodesetval->nodeNr; x++) {
    xml_node = this->obj->nodesetval->nodeTab[x];
    xml_value = xmlNodeListGetString(this->doc, xml_node->xmlChildrenNode, 1);

    // parse value and push to array
    value = reinterpret_cast<char *>(xml_value);
    if (type == BOOL_ARRAY) {
      // strip white space in string
      std::string v = std::string(value);
      strip(v, ' ');

      // parse bool
      if (v.compare("true") == 0 || v.compare("1") == 0) {
        reinterpret_cast<std::vector<bool> *>(out)->push_back(true);
      } else if (v.compare("false") == 0 || v.compare("0") == 0) {
        reinterpret_cast<std::vector<bool> *>(out)->push_back(false);
      } else {
        return EINVBOOLD;
      }

    } else if (type == INT_ARRAY) {
      i = atoi(value);
      reinterpret_cast<std::vector<int> *>(out)->push_back(i);

    } else if (type == FLOAT_ARRAY) {
      f = static_cast<float>(atof(value));
      reinterpret_cast<std::vector<float> *>(out)->push_back(f);

    } else if (type == DOUBLE_ARRAY) {
      d = atof(value);
      reinterpret_cast<std::vector<double> *>(out)->push_back(d);

    } else if (type == STRING_ARRAY) {
      s = strim(std::string(value));
      reinterpret_cast<std::vector<std::string> *>(out)->push_back(s);

    } else {
      return ECONVTYPE;
    }
  }

  // clean up
  xmlFree(xml_value);
  xmlXPathFreeObject(this->obj);
  this->obj = NULL;

  return 0;
}

int ConfigParser::parseVector(std::string key,
                              enum ConfigDataType type,
                              void *out) {
  int retval;
  xmlNode *xml_node;
  xmlChar *xml_value;
  std::vector<std::string> data;

  // pre-check
  retval = this->checkVector(key, type);
  if (retval != 0) {
    return retval;
  }

  // parse data
  this->getParamPointer(key + "/vec");
  xml_node = this->obj->nodesetval->nodeTab[0];
  xml_value = xmlNodeListGetString(this->doc, xml_node->xmlChildrenNode, 1);
  std::string s = std::string(reinterpret_cast<char *>(xml_value));
  split(s, ',', data);

  // convert std::vector to VEC
  // clang-format off
  if (type == VEC2) {
    Vec2 &v = *reinterpret_cast<Vec2 *>(out);
    v(0) = atof(data[0].c_str());
    v(1) = atof(data[1].c_str());

  } else if (type == VEC3) {
    Vec3 &v = *reinterpret_cast<Vec3 *>(out);
    v(0) = atof(data[0].c_str());
    v(1) = atof(data[1].c_str());
    v(2) = atof(data[2].c_str());

  } else if (type == VEC4) {
    Vec4 &v = *reinterpret_cast<Vec4 *>(out);
    v(0) = atof(data[0].c_str());
    v(1) = atof(data[1].c_str());
    v(2) = atof(data[2].c_str());
    v(3) = atof(data[3].c_str());

  } else if (type == VECX) {
    VecX &vecx = *reinterpret_cast<VecX *>(out);
    vecx = VecX(data.size());
    for (size_t i = 0; i < data.size(); i++) {
      vecx(i) = atof(data[i].c_str());
    }

  } else {
    return ECONVTYPE;
  }
  // clang-format on

  // clean up
  xmlFree(xml_value);
  xmlXPathFreeObject(this->obj);
  this->obj = NULL;

  return 0;
}

int ConfigParser::parseMatrix(std::string key,
                              enum ConfigDataType type,
                              void *out) {
  int retval, rows, cols, idx;
  xmlNode *xml_node;
  xmlChar *xml_value;
  std::vector<std::string> data;

  // pre-check
  retval = this->checkMatrix(key, type);
  if (retval != 0) {
    return retval;
  }

  // parse rows and cols
  this->parsePrimitive(key + "/rows", INT, &rows);
  this->parsePrimitive(key + "/cols", INT, &cols);

  // parse data
  this->getParamPointer(key + "/data");
  xml_node = this->obj->nodesetval->nodeTab[0];
  xml_value = xmlNodeListGetString(this->doc, xml_node->xmlChildrenNode, 1);
  std::string s = std::string(reinterpret_cast<char *>(xml_value));
  split(s, ',', data);

  // set matrix
  idx = 0;
  if (type == MAT2) {
    Mat2 &m = *reinterpret_cast<Mat2 *>(out);
    m(0, 0) = atof(data[0].c_str());
    m(0, 1) = atof(data[1].c_str());
    m(1, 0) = atof(data[2].c_str());
    m(1, 1) = atof(data[3].c_str());

  } else if (type == MAT3) {
    Mat3 &m = *reinterpret_cast<Mat3 *>(out);
    m(0, 0) = atof(data[0].c_str());
    m(0, 1) = atof(data[1].c_str());
    m(0, 2) = atof(data[2].c_str());

    m(1, 0) = atof(data[3].c_str());
    m(1, 1) = atof(data[4].c_str());
    m(1, 2) = atof(data[5].c_str());

    m(2, 0) = atof(data[6].c_str());
    m(2, 1) = atof(data[7].c_str());
    m(2, 2) = atof(data[8].c_str());

  } else if (type == MAT4) {
    Mat4 &m = *reinterpret_cast<Mat4 *>(out);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m(i, j) = atof(data[idx].c_str());
        idx++;
      }
    }

  } else if (type == MATX) {
    MatX &m = *reinterpret_cast<MatX *>(out);
    m.resize(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m(i, j) = atof(data[idx].c_str());
        idx++;
      }
    }

  } else if (type == CVMAT) {
    cv::Mat &m = *reinterpret_cast<cv::Mat *>(out);
    m = cv::Mat(rows, cols, CV_64F);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.at<double>(i, j) = atof(data[idx].c_str());
        idx++;
      }
    }

  } else {
    return ECONVTYPE;
  }

  return 0;
}

int ConfigParser::parsePrimitive(ConfigParam &param) {
  return this->parsePrimitive(param.key, param.type, param.data);
}

int ConfigParser::parseArray(ConfigParam &param) {
  return this->parseArray(param.key, param.type, param.data);
}

int ConfigParser::parseVector(ConfigParam &param) {
  return this->parseVector(param.key, param.type, param.data);
}

int ConfigParser::parseMatrix(ConfigParam &param) {
  return this->parseMatrix(param.key, param.type, param.data);
}

int ConfigParser::load(const std::string config_file) {
  int retval;

  // pre-check
  if (file_exists(config_file) == false) {
    log_err("File not found: %s", config_file.c_str());
    return -1;
  }

  // load and parse file
  this->doc = xmlReadFile(config_file.c_str(), NULL, XML_PARSE_NOERROR);
  if (this->doc == NULL) {
    log_err("Failed to parse [%s]!", config_file.c_str());
    return -2;
  } else {
    this->config_loaded = true;
  }

  for (int i = 0; i < (int) this->params.size(); i++) {
    switch (this->params[i].type) {
    // PRIMITIVE
    case BOOL:
    case INT:
    case FLOAT:
    case DOUBLE:
    case STRING:
      retval = this->parsePrimitive(this->params[i]);
      break;
    // ARRAY
    case BOOL_ARRAY:
    case INT_ARRAY:
    case FLOAT_ARRAY:
    case DOUBLE_ARRAY:
    case STRING_ARRAY:
      retval = this->parseArray(this->params[i]);
      break;
    // VECTOR
    case VEC2:
    case VEC3:
    case VEC4:
    case VECX:
      retval = this->parseVector(this->params[i]);
      break;
    // MAT
    case MAT2:
    case MAT3:
    case MAT4:
    case MATX:
    case CVMAT:
      retval = this->parseMatrix(this->params[i]);
      break;
    default:
      return -2;
      break;
    }

    if (retval != 0) {
      return retval;
    }
  }

  return 0;
}

}  // end of yarl namespace
