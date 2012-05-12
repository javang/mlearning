#include "gtest/gtest.h"
#include "trees/DecisionTree.h"
#include "trees/information_gain.h"
#include "utility/print_utils.h"

#include <vector>

/**
 * Fixture to text the measures of information  
 */
class DecisionTreeTest: public ::testing::Test {
protected:
  DecisionTreePtr tree_;
  unsigned int x;
  unsigned int y;
  MatrixXd golf_training_set;
  MatrixXd golf_trivial_set;
  std::vector<VariableType> golf_data_types;
  
  virtual void SetUp() {
    tree_ = DecisionTreePtr(new DecisionTree());
    

    golf_training_set.resize(28,5);
    // GOLF DATASET
    // 1st Column Outlook: sunny=0, overcast=1, rainy=2
    // 2nd column Temperature hot=0, mild=1, cool=2
    // 3rd Column Humidity high=0, normal=1
    // 4th column Windy true=1, false=0
    // 5th column Play yes=1, no=0
    golf_training_set <<  0, 0, 0, 0, 0,
                          0, 0, 0, 1, 0,
                          1, 0, 0, 0, 1,
                          2, 1, 0, 0, 1,
                          2, 2, 1, 0, 1,
                          2, 2, 1, 1, 0,
                          1, 2, 1, 1, 1,
                          0, 1, 0, 0, 0,
                          0, 2, 1, 0, 1,
                          2, 1, 1, 0, 1,
                          0, 1, 1, 1, 1,
                          1, 1, 0, 1, 1,
                          1, 0, 1, 0, 1,
                          2, 1, 0, 1, 0,
                          0, 0, 0, 0, 0,
                          0, 0, 0, 1, 0,
                          1, 0, 0, 0, 1,
                          2, 1, 0, 0, 1,
                          2, 2, 1, 0, 1,
                          2, 2, 1, 1, 0,
                          1, 2, 1, 1, 1,
                          0, 1, 0, 0, 0,
                          0, 2, 1, 0, 1,
                          2, 1, 1, 0, 1,
                          0, 1, 1, 1, 1,
                          1, 1, 0, 1, 1,
                          1, 0, 1, 0, 1,
                          2, 1, 0, 1, 0 ;

      golf_trivial_set.resize(5,5);
      golf_trivial_set << 0, 1, 1, 1, 0,
                          1, 1, 0, 0, 1,
                          0, 2, 1, 1, 0,
                          1, 1, 1, 1, 1,
                          2, 0, 0, 1, 0;

    
      for(unsigned int i = 0; i < golf_training_set.cols()-1; i++)
        golf_data_types.push_back(CATEGORICAL);
    
}
  
  virtual void TearDown() {};
    
};

TEST_F(DecisionTreeTest, ChildrenWork) {
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


TEST_F(DecisionTreeTest, TrivialSetOfInformationMeasure) {
  
  EXPECT_EQ(tree_->get_information_measure(),GINI);
  tree_->set_information_measure(ENTROPY);
  EXPECT_EQ(tree_->get_information_measure(), ENTROPY);
  tree_->set_information_measure(GINI);
  EXPECT_EQ(tree_->get_information_measure(), GINI);
}

TEST_F(DecisionTreeTest, TrivialCategoricalPrediction) {
  unsigned int rows = golf_trivial_set.rows();
  unsigned int cols = golf_trivial_set.cols();
  MatrixXd training_set = golf_trivial_set.topLeftCorner(rows,cols-2);
  VectorXi classes = golf_trivial_set.col(cols-1).cast<int>();
  DecisionTree dtree;
  dtree.train(training_set, classes, golf_data_types);
    
  VectorXi predictions = dtree.predict(training_set);
  std::cout << "predictions " << predictions << std::endl;
  // Should expect exactly what is in the sample
  EXPECT_EQ(predictions, classes);
}

