
#include "DecisionTreeTestFixture.h"
#include "gtest/gtest.h"
#include "trees/RandomForest.h"
#include "trees/information_gain.h"
#include "utility/print_utils.h"
#include "utility/read_matrix.h"
#include "measures/fscore.h"
#include "core/types.h"

TEST(DecisionTreeTestFixture, RandomForestPrediction) {
  
  // Read training data (UCI Iris dataset)
  MatrixXd training_set = read_matrix("trees/input/training_random_forest.txt",
                                      " ");
  unsigned int cols = training_set.cols();
  RandomForest random_forest(10);
  VariableTypes types = {CONTINUOUS, CONTINUOUS, CONTINUOUS, CONTINUOUS};
  random_forest.train(training_set.leftCols(cols-1),
                      training_set.rightCols(1),
                      types);
  MatrixXd test_set = read_matrix("test/input/test_random_forest.txt", " ");
  VectorXi predictions = random_forest.predict(test_set.leftCols(cols-1));
  // get fscore, precision, recall
  FScore f = get_fscore(predictions, test_set.rightCols(1).cast<int>());
  // This asserts are approximated based on previous runs
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, f.precision, 0.8);
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, f.recall, 0.8);
}

