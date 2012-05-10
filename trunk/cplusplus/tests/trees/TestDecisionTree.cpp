#include "trees/DecisionTree.h"
#include "trees/information_gain.h"

/**
 * Fixture to text the measures of information  
 */
class FixtureDecisionTree: public ::testing::Test {
protected:
  DecisionTree tree_;
  MatrixXd data(x,y);
  Bools are_categorical = { true, true, true, true, true};
  
  virtual void SetUp() {
  }
  
  virtual void TearDown() {};
    
};


TEST(TestDecisionTree, InfoMeasure) {
  
  EXPECT_EQ(tree_->get_information_measure(),GINI);
  tree_->set_information_measure(ENTROPY);
  EXPECT_EQ(tree_->get_information_measure(), ENTROPY);
  tree_->set_information_measure(GINI);
  EXPECT_EQ(tree_->get_information_measure(), GINI);
}

TEST_F(TestDecisionTree, InfoMeasure) {
  
  EXPECT_EQ(tree_->get_information_measure(),GINI);
  tree_->set_information_measure(ENTROPY);
  EXPECT_EQ(tree_->get_information_measure(), ENTROPY);
  tree_->set_information_measure(GINI);
  EXPECT_EQ(tree_->get_information_measure(), GINI);
}
