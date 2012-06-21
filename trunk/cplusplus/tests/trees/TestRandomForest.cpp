
#include "gtest/gtest.h"
#include "trees/RandomForest.h"
#include "trees/information_gain.h"
#include "utility/print_utils.h"
#include "utility/read_matrix.h"
#include "measures/fscore.h"
#include "core/types.h"

TEST(RandomForest, RandomForestPrediction) {
  // Read training data (UCI Iris dataset)
  String path = "trees/input/training_random_forest.txt";
  String delimiters = " ";
  MatrixXd training_set = read_matrix<double>(path, delimiters);
  unsigned int cols = training_set.cols();
  SupervisedClassifierPtr sup(new RandomForest(10));
  VariableTypes types = {CONTINUOUS, CONTINUOUS, CONTINUOUS, CONTINUOUS};
  sup->train(training_set.leftCols(cols-1), 
                                training_set.rightCols(1).cast<int>(), types);
  path = "test/input/test_random_forest.txt";
  MatrixXd test_set = read_matrix<double>(path, delimiters);
  VectorXi predictions = sup->predict(test_set.leftCols(cols-1));
  // get fscore, precision, recall
  FScore f;
  f.calculate(predictions, test_set.rightCols(1).cast<int>());
  // This asserts are approximated based on previous runs
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, f.get_precision()[0], 0.8);
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, f.get_recall()[0], 0.8);
}

