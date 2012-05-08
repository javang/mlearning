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



