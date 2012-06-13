
#include "DecisionTreeTestFixture.h"
#include "gtest/gtest.h"
#include "trees/RandomForest.h"
#include "trees/information_gain.h"
#include "utility/print_utils.h"
#include "measures/fscore.h"
//
//TEST(DecisionTreeTestFixture, RandomForestPrediction) {
//  
//  // Read training data (UCI Iris dataset)
//  
//  
//  RandomForest random_forest(10);
//  VariableTypes types = {CONTINUOUS, CONTINUOUS, CONTINUOUS, CONTINUOUS};
//  random_forest.train(data, classes, types);
//
//  // read test data
//  VectorXi predictions = random_forest.predict(test_data);
//  // get fscore, precision, recall
//  FScore f = get_fscore(predictions, test_classes);
//  // This asserts are approximated based on previous runs
//  EXPECT_PRED_FORMAT2(::testing::DoubleLE, f.precision, 0.8);
//  EXPECT_PRED_FORMAT2(::testing::DoubleLE, f.recall, 0.8);
//}