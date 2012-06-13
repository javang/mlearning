

#include "DecisionTreeTestFixture.h"
#include "gtest/gtest.h"
#include "trees/DecisionTree.h"
#include "trees/information_gain.h"
#include "utility/print_utils.h"
#include <vector>

TEST_F(DecisionTreeTestFixture, ChildrenWork) {
  // Check at the same type the casting for the children of a decision node 
  // and the trivial setting of the column for splitting
  DecisionNodePtr root(new DecisionNode());
  unsigned int n = 5;
  for(unsigned int i = 0; i < n; i++) {
    root->add_child(DecisionNodePtr(new DecisionNode()));
  }
  TreeNodePtrs children = root->get_children();
  for(unsigned int i = 0; i < n; i++) {
    DecisionNode *ptr = dynamic_cast<DecisionNode *>(children[i].get());
    ptr->set_column_for_next_split(i);
    EXPECT_EQ(ptr->get_column_for_next_split(), i);
  }

}


TEST_F(DecisionTreeTestFixture, TrivialSetOfInformationMeasure) {
  EXPECT_EQ(tree_->get_information_measure(),GINI);
  tree_->set_information_measure(ENTROPY);
  EXPECT_EQ(tree_->get_information_measure(), ENTROPY);
  tree_->set_information_measure(GINI);
  EXPECT_EQ(tree_->get_information_measure(), GINI);
}

TEST_F(DecisionTreeTestFixture, TrivialCategoricalPrediction) {
  tree_->set_information_measure(GINI);
  unsigned int rows = golf_test_set.rows();
  unsigned int cols = golf_test_set.cols();
  MatrixXd training_set = golf_test_set.topLeftCorner(rows,cols-1);
  VectorXi classes = golf_test_set.col(cols-1).cast<int>();
  DecisionTree dtree;
  dtree.train(training_set, classes, golf_data_types);
  VectorXi predictions = dtree.predict(training_set);
  // Should expect exactly what is in the sample
  EXPECT_EQ(predictions, classes);
}

TEST_F(DecisionTreeTestFixture, CategoricalPrediction) {
  tree_->set_information_measure(GINI);
  unsigned int rows = golf_training_set.rows();
  unsigned int cols = golf_training_set.cols();
  MatrixXd training_set = golf_training_set.topLeftCorner(rows,cols-1);
  VectorXi classes = golf_training_set.col(cols-1).cast<int>();
  DecisionTree dtree;
  dtree.train(training_set, classes, golf_data_types);
  MatrixXd test_set = golf_test_set.topLeftCorner(golf_test_set.rows(),
                                                  golf_test_set.cols()-1);
  VectorXi predictions = dtree.predict(test_set);
  VectorXi expected = golf_test_set.col(cols-1).cast<int>();
  EXPECT_EQ(predictions, expected);
}


TEST_F(DecisionTreeTestFixture,ContinuousCategoricalPrediction) {
  golf_training_set.col(2) = golf_continuous_humidity;
  golf_data_types[2] = CONTINUOUS;
  
  VectorXd continuous_humidity_test(5);
  continuous_humidity_test << 34, 76, 55, 34, 93;
  golf_test_set.col(2) = continuous_humidity_test;

  tree_->set_information_measure(GINI);
  unsigned int rows = golf_training_set.rows();
  unsigned int cols = golf_training_set.cols();
  MatrixXd training_set = golf_training_set.topLeftCorner(rows,cols-1);
  VectorXi classes = golf_training_set.col(cols-1).cast<int>();
  DecisionTreePtr dtree(new DecisionTree());
  dtree->train(training_set, classes, golf_data_types);
  MatrixXd test_set = golf_test_set.topLeftCorner(golf_test_set.rows(),
                                                  golf_test_set.cols()-1);
  VectorXi predictions = dtree->predict(test_set);
  VectorXi expected = golf_test_set.col(cols-1).cast<int>();
  EXPECT_EQ(predictions, expected);
}