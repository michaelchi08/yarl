#include "yarl/utils/config.hpp"

namespace yarl {

ConfigParser::ConfigParser(void) {
  this->config_loaded = false;
  this->doc = NULL;
  this->obj = NULL;
}

ConfigParser::~ConfigParser(void) {
  if (this->config_loaded) {
    xmlFreeDoc(this->doc);
    xmlCleanupParser();
  }

  if (this->obj) {
    xmlXPathFreeObject(this->obj);
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
  xpath = (xmlChar *) key.c_str();
  this->obj = xmlXPathEvalExpression(xpath, context);
  xmlXPathFreeContext(context);

  // check xpath results
  if (this->obj == NULL) {
    log_err("Invalid XPath [%s]", key.c_str());
    xmlXPathFreeObject(this->obj);
    this->obj = NULL;
    return EXPATHINV;

  } else if (xmlXPathNodeSetIsEmpty(this->obj->nodesetval)) {
    log_err("No result");
    xmlXPathFreeObject(this->obj);
    this->obj = NULL;
    return EXPATHRES;
  }

  return 0;
}

int ConfigParser::getPrimitive(int type, void *out) {
  xmlChar *value;

  // pre-check
  if (this->obj == NULL || this->obj->nodesetval == 0) {
    return EPARAMNAN;
  }

  // get value
  // clang-format off
  value = xmlNodeListGetString(
    this->doc,
    this->obj->nodesetval->nodeTab[0]->xmlChildrenNode,
    1
  );
  // clang-format on

  // convert value
  // clang-format off
  switch (type) {
    case 1: *(int *) out = atoi((const char *) value); break;
    case 2: *(double *) out = atof((const char *) value); break;
    case 3: *(std::string *) out = std::string((const char *) value); break;
    default: return ECONVTYPE;
  }
  // clang-format on

  // clean up
  xmlFree(value);
  xmlXPathFreeObject(this->obj);
  this->obj = NULL;

  return 0;
}

int ConfigParser::checkVector(std::string key,
                              enum ConfigDataType type,
                              bool optional) {
  int retval;
  int vector_size;

  // check key
  retval = this->getParamPointer(key);
  if (retval != 0) {
    return retval;
  }

  switch (type) {
    case VEC2:
      vector_size = 2;
      break;
    case VEC3:
      vector_size = 3;
      break;
    case VEC4:
      vector_size = 4;
      break;
    default:
      return 0;
  }

  // check number of values


  // if ((int) this->root[key].size() != vector_size) {
  //   // clang-format off
  //   log_err("Vector [%s] should have %d values but config has %d!",
  //     key.c_str(),
  //     vector_size,
  //     (int) this->root[key].size()
  //   );
  //   // clang-format on
  //   return -3;
  // }

  return 0;
}

// int ConfigParser::checkMatrix(const std::string key, const bool optional) {
//   int retval;
//   const std::string targets[3] = {"rows", "cols", "data"};
//
//   // check key
//   retval = this->checkKey(key, optional);
//   if (retval != 0) {
//     return retval;
//   }
//
//   // check fields
//   for (int i = 0; i < 3; i++) {
//     if (!this->root[key][targets[i]]) {
//       log_err("Key [%s] is missing for matrix [%s]!",
//               targets[i].c_str(),
//               key.c_str());
//       return -2;
//     }
//   }
//
//   return 0;
// }
//
// int ConfigParser::loadPrimitive(const ConfigParam param) {
//   int retval;
//   YAML::Node node;
//
//   // pre-check
//   retval = this->checkKey(param.key, param.optional);
//   if (retval != 0) {
//     return retval;
//   }
//
//   // parse
//   // clang-format off
//   this->getParam(param.key, node);
//   switch (param.type) {
//     case BOOL: *param.b = node.as<bool>(); break;
//     case INT: *param.i = node.as<int>(); break;
//     case FLOAT: *param.f = node.as<float>(); break;
//     case DOUBLE: *param.d = node.as<double>(); break;
//     case STRING: *param.s = node.as<std::string>(); break;
//     default: return -2;
//   }
//   // clang-format on
//
//   return 0;
// }
//
// int ConfigParser::loadArray(const ConfigParam param) {
//   int retval;
//   YAML::Node node;
//
//   // pre-check
//   retval = this->checkKey(param.key, param.optional);
//   if (retval != 0) {
//     return retval;
//   }
//
//   // parse
//   this->getParam(param.key, node);
//   switch (param.type) {
//     case BOOL_ARRAY:
//       for (size_t i = 0; i < node.size(); i++) {
//         param.b_array->push_back(node[i].as<bool>());
//       }
//       break;
//     case INT_ARRAY:
//       for (size_t i = 0; i < node.size(); i++) {
//         param.i_array->push_back(node[i].as<int>());
//       }
//       break;
//     case FLOAT_ARRAY:
//       for (size_t i = 0; i < node.size(); i++) {
//         param.f_array->push_back(node[i].as<float>());
//       }
//       break;
//     case DOUBLE_ARRAY:
//       for (size_t i = 0; i < node.size(); i++) {
//         param.d_array->push_back(node[i].as<double>());
//       }
//       break;
//     case STRING_ARRAY:
//       for (size_t i = 0; i < node.size(); i++) {
//         param.s_array->push_back(node[i].as<std::string>());
//       }
//       break;
//     default:
//       return -2;
//       break;
//   }
//
//   return 0;
// }
//
// int ConfigParser::loadVector(const ConfigParam param) {
//   int retval;
//   YAML::Node node;
//
//   // check
//   retval = this->checkVector(param.key, param.type, param.optional);
//   if (retval != 0) {
//     return retval;
//   }
//
//   // setup
//   Vec2 &vec2 = *param.vec2;
//   Vec3 &vec3 = *param.vec3;
//   Vec4 &vec4 = *param.vec4;
//   VecX &vecx = *param.vecx;
//
//   // parse
//   this->getParam(param.key, node);
//
//   switch (param.type) {
//     case VEC2:
//       vec2(0) = node[0].as<double>();
//       vec2(1) = node[1].as<double>();
//       break;
//     case VEC3:
//       vec3(0) = node[0].as<double>();
//       vec3(1) = node[1].as<double>();
//       vec3(2) = node[2].as<double>();
//       break;
//     case VEC4:
//       vec4(0) = node[0].as<double>();
//       vec4(1) = node[1].as<double>();
//       vec4(2) = node[2].as<double>();
//       vec4(3) = node[3].as<double>();
//       break;
//     case VECX:
//       vecx = VecX((int) node.size());
//       for (size_t i = 0; i < node.size(); i++) {
//         vecx(i) = node[i].as<double>();
//       }
//       break;
//     default:
//       return -2;
//       break;
//   }
//
//   return 0;
// }
//
// int ConfigParser::loadMatrix(const ConfigParam param) {
//   int retval;
//   int index;
//   int rows;
//   int cols;
//   YAML::Node node;
//
//   // pre-check
//   retval = this->checkMatrix(param.key, param.optional);
//   if (retval != 0) {
//     return retval;
//   }
//
//   // setup
//   Mat2 &mat2 = *param.mat2;
//   Mat3 &mat3 = *param.mat3;
//   Mat4 &mat4 = *param.mat4;
//   MatX &matx = *param.matx;
//   cv::Mat &cvmat = *param.cvmat;
//
//   // parse
//   this->getParam(param.key, node);
//   index = 0;
//   rows = node["rows"].as<int>();
//   cols = node["cols"].as<int>();
//
//   switch (param.type) {
//     case MAT2:
//       mat2(0, 0) = node["data"][0].as<double>();
//       mat2(0, 1) = node["data"][1].as<double>();
//
//       mat2(1, 0) = node["data"][2].as<double>();
//       mat2(1, 1) = node["data"][3].as<double>();
//       break;
//     case MAT3:
//       mat3(0, 0) = node["data"][0].as<double>();
//       mat3(0, 1) = node["data"][1].as<double>();
//       mat3(0, 2) = node["data"][2].as<double>();
//
//       mat3(1, 0) = node["data"][3].as<double>();
//       mat3(1, 1) = node["data"][4].as<double>();
//       mat3(1, 2) = node["data"][5].as<double>();
//
//       mat3(2, 0) = node["data"][6].as<double>();
//       mat3(2, 1) = node["data"][7].as<double>();
//       mat3(2, 2) = node["data"][8].as<double>();
//       break;
//     case MAT4:
//       for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//           mat4(i, j) = node["data"][index].as<double>();
//           index++;
//         }
//       }
//       break;
//     case MATX:
//       matx.resize(rows, cols);
//       for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//           matx(i, j) = node["data"][index].as<double>();
//           index++;
//         }
//       }
//       break;
//     case CVMAT:
//       cvmat = cv::Mat(rows, cols, CV_64F);
//       for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//           cvmat.at<double>(i, j) = node["data"][index].as<double>();
//           index++;
//         }
//       }
//       break;
//     default:
//       return -2;
//       break;
//   }
//
//   return 0;
// }

int ConfigParser::load(const std::string config_file) {
  // pre-check
  if (file_exists(config_file) == false) {
    log_err("File not found: %s", config_file.c_str());
    return -1;
  }

  // load and parse file
  xmlInitParser();
  this->doc = xmlReadFile(config_file.c_str(), NULL, XML_PARSE_NOERROR);
  if (this->doc == NULL) {
    log_err("Failed to parse [%s]!", config_file.c_str());
    return -2;
  } else {
    this->config_loaded = true;
  }

  // for (int i = 0; i < (int) this->params.size(); i++) {
  //   switch (this->params[i].type) {
  //     // PRIMITIVE
  //     case BOOL:
  //     case INT:
  //     case FLOAT:
  //     case DOUBLE:
  //     case STRING:
  //       // retval = this->loadPrimitive(this->params[i]);
  //       break;
  //     // ARRAY
  //     case BOOL_ARRAY:
  //     case INT_ARRAY:
  //     case FLOAT_ARRAY:
  //     case DOUBLE_ARRAY:
  //     case STRING_ARRAY:
  //       // retval = this->loadArray(this->params[i]);
  //       break;
  //     // VECTOR
  //     case VEC2:
  //     case VEC3:
  //     case VEC4:
  //     case VECX:
  //       // retval = this->loadVector(this->params[i]);
  //       break;
  //     // MAT
  //     case MAT2:
  //     case MAT3:
  //     case MAT4:
  //     case MATX:
  //     case CVMAT:
  //       // retval = this->loadMatrix(this->params[i]);
  //       break;
  //     default:
  //       return -2;
  //       break;
  //   }

  // if (retval != 0) {
  //   return retval;
  // }
  // }

  return 0;
}

}  // end of yarl namespace
