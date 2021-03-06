
#include "gtest/gtest.h"
#include "utility/read_matrix.h"
#include "utility/errors.h"
#include <iostream>
using namespace ml;
using namespace ml::utility;
using namespace Eigen;

TEST(TestReadMatrix, NotFile) {
  ASSERT_THROW(read_matrix<double>("NotFile.txt", " "), std::ios_base::failure);
}

TEST(TestReadMatrix, GoodIntMatrix) {
  
  //TODO: Find a way of locating the file on disk
  MatrixXi M = read_matrix<int>("input/good_int_matrix.txt", " ,");
  MatrixXi expected(3,4);
  expected << 3, 1, 6, 8,
              1, 53, -13, 456,
              4, 4, 0, -1;
  EXPECT_EQ(M, expected);
}

TEST(TestReadMatrix, GoodDoubleMatrix) {
  MatrixXd M = read_matrix<double>("input/good_double_matrix.txt", " ,");
  MatrixXd expected(3,4);
  expected << 3.23, 1.34, 6.57, 8.15,
            1.37, -13.6, 456.3, 4.3,
            4, 4.2, 0, -1.234;
  EXPECT_EQ(M, expected);
  // changed added from branch fix_readmatrix on chime
}

TEST(TestReadMatrix, BadDoubleMatrix) {
  ASSERT_THROW(read_matrix<double>("input/bad_double_matrix.txt", " ,"), SizeError);
}
