/* 
 * File:   test_eigen_helper.cpp
 * Author: javi
 *
 * Created on Apr 11, 2012, 12:09:45 AM
 */

#include "gtest/gtest.h"
#include "utility/eigen_helper.h"
#include "definitions.h"
#include <iostream>
#include <limits>
using namespace ml;
using namespace ml::utility;
using namespace Eigen;

TEST(TestEigenHelper, TestDivideColwise) {
  MatrixXd M(4,3);
  M << 1, 2, 3,
       8, 7, 2,
       2, 4, 3,
       1, 3, 9;
  VectorXd v(4,1);
  v << 1, 2, 3, 4;
  MatrixXd expected(4,3);
  expected << 1.0, 2.0, 3.0,
       8.0/2, 7.0/2, 2.0/2,
       2.0/3, 4.0/3, 3.0/3,
       1.0/4, 3.0/4, 9.0/4;
  MatrixXd R = divide_colwise(M, v);
  MatrixXd dif = (R - expected);
  dif.array().abs();
  double epsilon = std::numeric_limits<double>::epsilon();
  EXPECT_TRUE( (dif.array() < epsilon).all() );
}


TEST(TestEigenHelper, TestSelectColumns) {
  unsigned int rows = 4;
  unsigned int cls = 5;
  MatrixXi v(rows, cls);
  v << 1, 2, 3, 4, 5,
       6, 7, 8, 9, 10,
       11, 12, 13, 14, 15,
       16, 17, 18, 19, 20;
  std::vector<int> cols = {0,1,4};
  MatrixXi z = select_columns<int, Ints >(v, cols);
  EXPECT_EQ(v.col(0), z.col(0));
  EXPECT_EQ(v.col(1), z.col(1));
  EXPECT_EQ(v.col(4), z.col(2));

  MatrixXd q = v.cast<double>() / 2;
  Ints more_cols = {1,0,2};
  MatrixXd t = select_columns<double, Ints >(q, more_cols);
  for(unsigned int i = 0; i < rows; i++) {
    EXPECT_DOUBLE_EQ(q(i, 1), t(i, 0));
    EXPECT_DOUBLE_EQ(q(i, 0), t(i, 1));
    EXPECT_DOUBLE_EQ(q(i, 2), t(i, 2));
  }

}

TEST(TestEigenHelper, TestSelectRows) {
  unsigned int rows = 4;
  unsigned int cols = 5;
  MatrixXi v(rows, cols);
  v << 1, 2, 3, 4, 5,
       6, 7, 8, 9, 10,
       11, 12, 13, 14, 15,
       16, 17, 18, 19, 20;
  Ints myrows = {1,3};
  MatrixXi z = select_rows<int, Ints >(v, myrows);
  EXPECT_EQ(v.row(1), z.row(0));
  EXPECT_EQ(v.row(3), z.row(1));

  MatrixXd q = v.cast<double>() / 2;
  Ints more_rows = {1,0,2};
  MatrixXd t = select_rows<double, Ints >(q, more_rows);
  for(unsigned int i = 0; i < cols; i++) {
    EXPECT_DOUBLE_EQ(q(1, i), t(0, i));
    EXPECT_DOUBLE_EQ(q(0, i), t(1, i));
    EXPECT_DOUBLE_EQ(q(2, i), t(2, i));
  }

}
