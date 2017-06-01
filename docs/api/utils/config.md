# yarl/utils/config.hpp

The `yarl/utils/config.hpp` contains a useful `ConfigParser` class to simplify parsing yaml files.

- ConfigDataType
- ConfigParam
- ConfigParser
- Example Code

## ConfigDataType

    namespace yarl {

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

    }  // namespace yarl

The `ConfigDataType` is an enum used by `ConfigParam` to denote the yaml value
type. At current we support parsing of the following data types:

- **Primitives**: `bool`, `int`, `float`, `double`, `std::string`
- **Arrays**: `std::vector<bool>`, `std::vector<int>`, `std::vector<float>`,
  `std::vector<double>`, `std::vector<std::string>`
- **Vectors**: `Eigen::Vector2d`, `Eigen::Vector3d`, `Eigen::Vector4d`,
  `Eigen::VectorXd`
- **Matrices**: `Eigen::Matrix2d`, `Eigen::Matrix3d`, `Eigen::Matrix4d`,
  `Eigen::MatrixXd`


## ConfigParam

    namespace yarl {

    class ConfigParam {
    public:
        enum ConfigDataType type;
        std::string key;
        void *data;
        bool optional;

        ConfigParam();
    };

    }  // namespace yarl

Each parameter to be parsed in the yaml file is represented by a `ConfigParam`,
where:

- `ConfigParam.type`: parameter type (e.g `int`, `float`, etc)
- `ConfigParam.key`: yaml key to parse from
- `ConfigParam.data`: pointer to variable to store the parameter value

By default an instance of `ConfigParam` will have:

- `type` set to `TYPE_NOT_SET`
- `key` set to ""
- `data` set to `NULL`


## ConfigParser

    namespace yarl {

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

    }  // namespace yarl

### Constructor

    ConfigParser()

The default `ConfigParser` does not take any arguments, by default it sets:

- `config_loaded` to `false`

This variable is set to `true` once the yaml file is loaded.


### Methods

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

Use this to add parameters you would like to parse from the yaml file, where
`key` is the yaml key, `out` is dependent on the type of parameter you want to
parse to and an `optional` parameter to define whether `ConfigParser` should
fail if the parameter is not found.

Currently `ConfigParser` supports parsing the following data types:

- **Primitives**: `bool`, `int`, `float`, `double`, `std::string`
- **Arrays**: `std::vector<bool>`, `std::vector<int>`, `std::vector<float>`,
  `std::vector<double>`, `std::vector<std::string>`
- **Vectors**: `Eigen::Vector2d`, `Eigen::Vector3d`, `Eigen::Vector4d`,
  `Eigen::VectorXd`
- **Matrices**: `Eigen::Matrix2d`, `Eigen::Matrix3d`, `Eigen::Matrix4d`,
  `Eigen::MatrixXd`

**Important!**: For a **matrix** we require the yaml to have three nested keys
in order for `ConfigParser` to operate properly, they are `rows`, `cols` and
`data`, for example:

    some_matrix:
      rows: 3
      cols: 3
      data: [1.1, 2.2, 3.3,
            4.4, 5.5, 6.6,
            7.7, 8.8, 9.9]

---

    int getYamlNode(std::string key, YAML::Node &node);

Get yaml node give yaml `key`, the result is set to `node` if `key` matches
anything in the config file, else `node` is set to `NULL`.

Returns:

- `0`: On success
- `-1`: Config file is not loaded

---

    int checkKey(const std::string &key, bool optional);
    int checkVector(const std::string &key, enum ConfigDataType type, bool optional);
    int checkMatrix(const std::string &key, bool optional);

Returns:

- `0`: On success
- `-1`: Config file is not loaded
- `-2`: `key` not found in yaml file, parameter is not optional
- `-3`: `key` not found in yaml file, parameter is optional
- `-4`: Invalid vector (wrong size)
- `-5`: Invalid matrix (missing yaml key 'rows', 'cols' or 'data' for matrix)

---

    int loadPrimitive(const ConfigParam &param);
    int loadArray(const ConfigParam &param);
    int loadVector(const ConfigParam &param);
    int loadMatrix(const ConfigParam &param);

Load yaml param primitive, array, vector or matrix.

Returns:

- `0`: On success
- `-1`: Config file is not loaded
- `-2`: `key` not found in yaml file, parameter is not optional
- `-3`: `key` not found in yaml file, parameter is optional
- `-4`: Invalid vector (wrong size)
- `-5`: Invalid matrix (missing yaml key 'rows', 'cols' or 'data' for matrix)
- `-6`: Invalid param type

---

    int load(const std::string &config_file);

Load yaml file at `config_file`.

Returns:

- `0`: On success
- `1`: File not found
- `-1`: Config file is not loaded
- `-2`: `key` not found in yaml file
- `-4`: Invalid vector (wrong size)
- `-5`: Invalid matrix (missing yaml key 'rows', 'cols' or 'data' for matrix)
- `-6`: Invalid param type



## Example Code

Consider this yaml file:

    controller:
        min: -30.0
        max: 30.0
        kp: 0.4
        ki: 0.0
        kd: 0.3

The code that parses the above becomes:

    #include "yarl/utils/config.hpp"

    yarl::ConfigParser parser;

    double kp, ki, kd;
    double roll_limit[2];

    // tell the parser what to parse
    parser.addParam("controller.k_p", &kp);
    parser.addParam("controller.k_i", &ki);
    parser.addParam("controller.k_d", &kd);
    parser.addParam("controller.min", &roll_limit[0]);
    parser.addParam("controller.max", &roll_limit[1]);

    // parser.addParam("controller.max", &roll_limit[1]);
    //                        ^                ^
    //                        |                |
    // yaml key --------------+                |
    // variable to store config value  --------+
    //
    // Note: We support the dot notation for yaml keys

    // load the config file and assign values to variables
    if (parser.load(config_file) != 0) {
      return -1;
    }

Currently `ConfigParser` supports parsing the following data types:

- **Primitives**: `bool`, `int`, `float`, `double`, `std::string`
- **Arrays**: `std::vector<bool>`, `std::vector<int>`, `std::vector<float>`,
  `std::vector<double>`, `std::vector<std::string>`
- **Vectors**: `Eigen::Vector2d`, `Eigen::Vector3d`, `Eigen::Vector4d`,
  `Eigen::VectorXd`
- **Matrices**: `Eigen::Matrix2d`, `Eigen::Matrix3d`, `Eigen::Matrix4d`,
  `Eigen::MatrixXd`
