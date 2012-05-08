/* 
 * File:   InfoGainTest.cpp
 * Author: javi
 *
 * Created on Apr 11, 2012, 12:09:45 AM
 */

#include "gtest/gtest.h"
#include <iostream>
#include "trees/information_gain.h"
#include "algorithms/argsort.h"

TEST(InfoGainTest, TestGetCrossTable) {
  VectorXi classes(10);
  classes << 1, 2, 2, 1, 3, 1, 3, 2, 1, 1;
  VectorXi values(10);
  values <<  1, 1, 1, 3, 4, 0, 4, 4, 5, 3;
  MatrixXi result = get_cross_table(values, classes);
  MatrixXi expected(5,3);
  expected <<  1, 0, 0,
               1, 2, 0,
               2, 0, 0,
               0, 1, 2,
               1, 0, 0;
  EXPECT_TRUE( (result == expected));
}

TEST(InfoGainTest, TestGetCrossTable1D) {
  VectorXi values(10);
  values <<  1, 1, 1, 3, 4, 0, 4, 4, 5, 3;
  VectorXi result = get_cross_table(values);
  VectorXi expected(5,1);
  expected <<  1, 3, 2, 3, 1;
  EXPECT_EQ( result, expected);
}

/**
 * Fixture to text the measures of information  
 */
class InformationMeasuresTest: public ::testing::Test {
protected:
  VectorXi classes_;
  VectorXd values_double_;
  VectorXi values_int_;

  virtual void SetUp() {
    classes_.resize(6);
    classes_ << 1, 1, 1, 1, 1, 1;
    values_double_.resize(6);
    values_double_ << 3.23, 3.89, 1.34234, 3.435, 2.34348, 0.2131;
    values_int_.resize(6);
    values_int_ << 1, 2, 3, 4, 5, 6;
  }
  
  virtual void TearDown() {};
    
};

TEST_F(InformationMeasuresTest, ContinuousEntropy) {
  GainPair g = continuous_entropy_gain(values_double_, classes_);
  EXPECT_NEAR(0, g.first, 1e-10);
  classes_ << 1, 1, 0, 1, 0, 0;
  g = continuous_entropy_gain(values_double_, classes_);
  EXPECT_NEAR(1, g.first, 1e-10);
  classes_ << 0, 1, 0, 1, 1, 1;
  g = continuous_entropy_gain(values_double_, classes_);
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, g.first, 1);
}


TEST_F(InformationMeasuresTest, NominalEntropy) {
  double g = nominal_entropy_gain(values_int_, classes_);
  EXPECT_NEAR(0, g, 1e-10);
  classes_ << 0, 0, 0, 1, 1, 1;
  values_int_ << 3, 3, 3, 4, 4, 4;
  g = nominal_entropy_gain(values_int_, classes_);
  EXPECT_NEAR(1, g, 13-10);
  values_int_ << 3, 4, 3, 4, 4, 4;
  g = nominal_entropy_gain(values_int_, classes_);
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, g, 1);
}

TEST_F(InformationMeasuresTest, ContinuousGini) {
  GainPair g = continuous_gini_gain(values_double_, classes_);
  EXPECT_NEAR(0, g.first, 1e-10);
  classes_ << 1, 1, 0, 1, 0, 0;
  g = continuous_gini_gain(values_double_, classes_);
  EXPECT_NEAR(0.5, g.first, 1e-10);
  classes_ << 0, 1, 0, 1, 1, 1;
  g = continuous_gini_gain(values_double_, classes_);
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, g.first, 0.5);
}

TEST_F(InformationMeasuresTest, NominalGini) {
  double g = nominal_gini_gain(values_int_, classes_);
  EXPECT_DOUBLE_EQ(0, g);
  classes_ << 0, 0, 0, 1, 1, 1;
  values_int_ << 3, 3, 3, 4, 4, 4;
  g = nominal_gini_gain(values_int_, classes_);
  EXPECT_DOUBLE_EQ(0.5, g);
  values_int_ << 3, 4, 3, 4, 4, 4;
  g = nominal_gini_gain(values_int_, classes_);
  EXPECT_PRED_FORMAT2(::testing::DoubleLE, g, 0.5);
}


