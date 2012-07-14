/* 
 * File:   DecisionTreeTest.h
 * Author: javi
 *
 * Created on June 8, 2012, 10:32 AM
 */

#ifndef DECISIONTREETESTFIXTURE_H
#define	DECISIONTREETESTFIXTURE_H


#include "gtest/gtest.h"
#include "trees/DecisionTree.h"
#include "trees/information_gain.h"
#include "utility/eigen_helper.h"
#include <vector>


/**
 * Fixture to text the measures of information  
 */
class DecisionTreeTestFixture: public ::testing::Test {
protected:
  ml::trees::DecisionTreePtr tree_;
  unsigned int x;
  unsigned int y;
  Eigen::MatrixXd golf_training_set;
  Eigen::MatrixXd golf_test_set;
  Eigen::VectorXd golf_continuous_humidity;
  std::vector<ml::VariableType> golf_data_types;
  
  virtual void SetUp() {
    tree_ = ml::trees::DecisionTreePtr(new ml::trees::DecisionTree());
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

      golf_test_set.resize(5,5);
      golf_test_set <<    0, 1, 1, 1, 1,
                          1, 1, 0, 0, 1,
                          0, 2, 1, 1, 1,
                          1, 1, 1, 1, 1,
                          2, 0, 0, 1, 0;

      golf_continuous_humidity.resize(28);
      golf_continuous_humidity << 82, 97, 76, 90, 52, 47, 23, 87, 34, 72, 61,
              98, 50, 84, 78, 89, 90, 91, 54, 44, 34, 79, 22, 12, 34, 86, 12,
              95;
      

      for(unsigned int i = 0; i < golf_training_set.cols()-1; i++)
        golf_data_types.push_back(ml::CATEGORICAL);
    
}
  virtual void TearDown() {};
};


#endif	/* DECISIONTREETEST_H */

