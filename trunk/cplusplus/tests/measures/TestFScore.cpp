#include "gtest/gtest.h"
#include "measures/fscore.h"
#include <functional>
#include "algorithms/confusion_matrix.h"

using namespace ml;
using namespace ml::algorithms;
using namespace ml::measures;
using namespace Eigen;

TEST(TestMeasures, AvoidZero) {
  VectorXi v(5);
  v << 1, 2, 4, 0, 0;
  VectorXi expected(5);
  expected << 1, 2, 4, 1, 1;
  VectorXi w = v.unaryExpr(std::ptr_fun(avoid_zero));
  EXPECT_EQ(expected, w);
}

TEST(TestMeasures, FScore) {
  Ints classes =     {3,2,1,1,1,2,3,1,2,1,1,4}; 
  Ints predictions = {1,3,1,2,1,3,1,2,2,1,1,1}; 
  
  FScore f;
  f.calculate(predictions, classes);
  VectorXd recall(4);
  recall << 4.0/6, 1.0/3, 0, 0;
  VectorXd precision(4);
  precision << 4.0/7, 1.0/3, 0, 0;
  VectorXd sum = (recall + precision).unaryExpr(std::ptr_fun(avoid_zero_double));
  VectorXd fscore = 2 * recall.array() * precision.array() / sum.array();
          (recall.array() + precision.array());
  for(int i = 0; i < recall.size(); ++i) {
    EXPECT_DOUBLE_EQ(recall[i], f.get_recall()[i]);
    EXPECT_DOUBLE_EQ(precision[i], f.get_precision()[i]);
    EXPECT_DOUBLE_EQ(fscore[i], f.get_fscore()[i]);
  }
}
