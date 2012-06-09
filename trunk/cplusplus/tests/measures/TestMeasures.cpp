#include "gtest/gtest.h"
#include "measures/fscore.h"
#include <functional>

TEST(TestMeasures, AvoidZero) {
  VectorXi v(5);
  v << 1, 2, 4, 0, 0;
  VectorXi expected(5);
  expected << 1, 2, 4, 1, 1;
  v.UnaryExp(std::function<avoid_zero(int)>);
  EXPECT_EQ(expected, v);
}

TEST(TestMeasures, FScore) {
  Ints classes =     {3,2,1,1,1,2,3,1,2,1,1,4};
  Ints predictions = {1,3,1,2,1,3,1,2,2,1,1,1};
  FScore f = get_fscore(predictions, classes);
  
  VectorXd recall(4);
  recall << 4.0/6, 1.0/3, 0, 0;
  VectorXd precision(4);
  precision << 4.0/7, 1.0/3, 0, 0;
  VectorXd fscore = 2 * recall.array() * precision.array() / 
          (recall.array() + precision.array());
  
  for(unsigned int i = 0; i < recall.size(); ++i) {
    EXPECT_DOUBLE_EQ(recall[i], f.recall[i]);
    EXPECT_DOUBLE_EQ(precision[i], f.precision[i]);
    EXPECT_DOUBLE_EQ(fscore[i], f.fscore[i]);
  }
}
