
#include "gtest/gtest.h"
#include "algorithms/confusion_matrix.h"
#include "utility/eigen_helper.h"
#include "types.h"
#include <iostream>
#include <functional>

using namespace ml;
using namespace ml::algorithms;
using namespace ml::utility;
using namespace Eigen;


TEST(TestConfusionMatrix, CheckCalculation) {
  Ints classes =     {3,2,1,1,1,2,3,1,2,1,1,4};
  Ints predictions = {1,3,1,2,1,3,1,2,2,1,1,1};
  MatrixXi cmat = get_confusion_matrix(predictions.begin(), predictions.end(),
                                       classes.begin(), classes.end());
  MatrixXi expected(4,4);
  expected << 4,0,2,1,
              2,1,0,0,
              0,2,0,0,
              0,0,0,0;
  EXPECT_EQ(expected, cmat);
}


TEST(TestConfusionMatrix, CheckTemplatedFunction) {
  Ints classes =     {3,2,1,1,1,2,3,1,2,1,1,4};
  Ints predictions = {1,3,1,2,1,3,1,2,2,1,1,1};
  MatrixXi cmat = get_confusion_matrix(predictions,classes);
  MatrixXi expected(4,4);
  expected << 4,0,2,1,
              2,1,0,0,
              0,2,0,0,
              0,0,0,0;
  EXPECT_EQ(expected, cmat);
}
