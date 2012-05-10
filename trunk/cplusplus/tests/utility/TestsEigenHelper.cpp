/* 
 * File:   test_eigen_helper.cpp
 * Author: javi
 *
 * Created on Apr 11, 2012, 12:09:45 AM
 */

#include "gtest/gtest.h"
#include <iostream>
#include "utility/eigen_helper.h"
#include <limits>

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
  MatrixXi v(4,5);
  v << 1, 2, 3, 4, 5,
       6, 7, 8, 9, 10,
       11, 12, 13, 14, 15,
       16, 17, 18, 19, 20;
  std::vector<int> cols = {0,1,4};
  MatrixXi z = select_columns<int, std::vector<int> >(v, cols);
  EXPECT_EQ(v.col(0), z.col(0));
  EXPECT_EQ(v.col(1), z.col(1));
  EXPECT_EQ(v.col(4), z.col(2));

  MatrixXd q = v.cats<double>() / 2;
  std::vector<int> more_cols = {1,0,2};
  MatrixXi t = select_columns<double, std::vector<int> >(q, more_cols);
  EXPECT_DOUBLE_EQ(q.col(1), t.col(0));
  EXPECT_DOUBLE_EQ(q.col(0), t.col(1));
  EXPECT_DOUBLE_EQ(q.col(2), t.col(2));
}
