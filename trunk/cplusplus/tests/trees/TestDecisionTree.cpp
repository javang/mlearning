#include "gtest/gtest.h"
#include "trees/DecisionTree.h"
#include "trees/information_gain.h"

/**
 * Fixture to text the measures of information  
 */
class DecisionTreeTest: public ::testing::Test {
protected:
  DecisionTreePtr tree_;
  unsigned int x;
  unsigned int y;
  std::vector<VariableType> vtypes;
  
  virtual void SetUp() {
    tree_ = DecisionTreePtr(new DecisionTree());
    unsigned int x = 10;
    unsigned int y = 5;
    MatrixXd data(x,y);
    for(unsigned int i = 0; i < y; i++) {
      vtypes.push_back(CATEGORICAL);
    }

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
