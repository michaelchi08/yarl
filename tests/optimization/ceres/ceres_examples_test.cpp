#include "yarl/test.hpp"
#include "yarl/utils/utils.hpp"
#include "yarl/optimization/ceres/ceres_examples.hpp"


namespace yarl {

TEST(CeresExamples, runAutoDiffExample) {
  runAutoDiffExample();
}

TEST(CeresExamples, runNumericalDiffExample) {
  runNumericalDiffExample();
}

TEST(CeresExamples, runAnalyticalDiffExample) {
  runAnalyticalDiffExample();
}

TEST(CeresExamples, runCurveFittingExample) {
  runCurveFittingExample();
}

}  // namespace yarl
