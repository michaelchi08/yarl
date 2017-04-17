#ifndef YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP
#define YARL_OPTIMIZATION_FACTOR_GRAPH_FACTOR_HPP

#include <memory>

#include "yarl/utils/utils.hpp"
#include "yarl/optimization/factor_graph/variable.hpp"

namespace yarl {

enum class FactorType { NOT_SET = 0, UNARY = 1, BINARY = 2, VO = 3 };
enum class FactorDataType {
  NOT_SET = 0,
  DOUBLE = 1,
  VEC2 = 2,
  VEC3 = 3,
  VEC4 = 4,
  VECX = 5,
  MAT2 = 6,
  MAT3 = 7,
  MAT4 = 8,
  MATX = 9,
  CVMAT = 10
};

// struct BaseFactor {
//   FactorType factor_type;
//   std::vector<std::shared_ptr<Variable>> variables;
//   FactorDataType data_type;
//   void *measurement;
//
//   BaseFactor()
//     : factor_type{FactorType::NOT_SET},
//       variables{},
//       data_type{FactorDataType::NOT_SET},
//       measurement{nullptr} {}
// };

struct Factor {
  FactorType factor_type;
  std::vector<std::shared_ptr<Variable>> variables;
  FactorDataType data_type;
  void *measurement;

  Factor(const std::shared_ptr<Variable> &at, const double &measurement)
    : factor_type{FactorType::UNARY},
      variables{at},
      data_type{FactorDataType::DOUBLE},
      measurement{nullptr} {
    this->measurement = new double(measurement);
  }

  Factor(const std::shared_ptr<Variable> &at, const Vec2 &measurement)
    : factor_type{FactorType::UNARY},
      variables{at},
      data_type{FactorDataType::VEC2},
      measurement{nullptr} {
    this->measurement = new Vec2();
    *static_cast<Vec2 *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &at, const Vec3 &measurement)
    : factor_type{FactorType::UNARY},
      variables{at},
      data_type{FactorDataType::VEC3},
      measurement{nullptr} {
    this->measurement = new Vec3();
    *static_cast<Vec3 *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &at, const Vec4 &measurement)
    : factor_type{FactorType::UNARY},
      variables{at},
      data_type{FactorDataType::VEC4},
      measurement{nullptr} {
    this->measurement = new Vec4();
    *static_cast<Vec4 *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &at, const VecX &measurement)
    : factor_type{FactorType::UNARY},
      variables{at},
      data_type{FactorDataType::VECX},
      measurement{nullptr} {
    this->measurement = new VecX();
    *static_cast<VecX *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &from,
         const std::shared_ptr<Variable> &to,
         const double &measurement)
    : factor_type{FactorType::BINARY},
      variables{from, to},
      data_type{FactorDataType::DOUBLE},
      measurement{nullptr} {
    this->measurement = new double(measurement);
  }

  Factor(const std::shared_ptr<Variable> &from,
         const std::shared_ptr<Variable> &to,
         const Vec2 &measurement)
    : factor_type{FactorType::BINARY},
      variables{from, to},
      data_type{FactorDataType::VEC2},
      measurement{nullptr} {
    this->measurement = new Vec2();
    *static_cast<Vec2 *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &from,
         const std::shared_ptr<Variable> &to,
         const Vec3 &measurement)
    : factor_type{FactorType::BINARY},
      variables{from, to},
      data_type{FactorDataType::VEC3},
      measurement{nullptr} {
    this->measurement = new Vec3();
    *static_cast<Vec3 *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &from,
         const std::shared_ptr<Variable> &to,
         const Vec4 &measurement)
    : factor_type{FactorType::BINARY},
      variables{from, to},
      data_type{FactorDataType::VEC4},
      measurement{nullptr} {
    this->measurement = new Vec4();
    *static_cast<Vec4 *>(this->measurement) = measurement;
  }

  Factor(const std::shared_ptr<Variable> &from,
         const std::shared_ptr<Variable> &to,
         const VecX &measurement)
    : factor_type{FactorType::BINARY},
      variables{from, to},
      data_type{FactorDataType::VECX},
      measurement{nullptr} {
    this->measurement = new VecX();
    *static_cast<VecX *>(this->measurement) = measurement;
  }

  ~Factor() {
    switch (this->data_type) {
      case FactorDataType::DOUBLE:
        delete static_cast<double *>(this->measurement);
        break;
      case FactorDataType::VEC2:
        delete static_cast<Vec2 *>(this->measurement);
        break;
      case FactorDataType::VEC3:
        delete static_cast<Vec3 *>(this->measurement);
        break;
      case FactorDataType::VEC4:
        delete static_cast<Vec4 *>(this->measurement);
        break;
      default: break;
    }
    this->measurement = NULL;
  }

  std::string toString() {
    std::ostringstream oss;

    switch (this->factor_type) {
      case FactorType::UNARY:
        oss << "[type: unary, ";
        oss << "at: " << this->variables[0]->id;
        oss << "]";
        break;
      case FactorType::BINARY:
        oss << "[type: binary, ";
        oss << "from: " << this->variables[0]->id;
        oss << ", ";
        oss << "to: " << this->variables[1]->id;
        oss << "]";
        break;
      default: break;
    }

    return oss.str();
  }

  void print() {
    std::cout << this->toString() << std::endl;
  }
};

}  // end of yarl namespace
#endif
