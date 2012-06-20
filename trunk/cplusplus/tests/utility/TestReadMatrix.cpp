
#include "gtest/gtest.h"
#include "utility/read_matrix.h"
#include "utility/errors.h"
#include <iostream>

TEST(TestReadMatrix, NotFile) {
  ASSERT_TRHOW(read_matrix("NotFile.txt", " "), std::ios_base::failure);
}

TEST(TestReadMatrix, GoodIntMatrix) {
  MatrixXi M = read_matrix("good_int_matrix.txt", " ,");
  MatrixXi expected(4,3);
  expected << 3, 1, 6, 8,
              1, -13, 456,
              4, 4, 0, -1;
  EXPECT_EQ(M, expected);
}

TEST(TestReadMatrix, GoodDoubleMatrix) {
  MatrixXd M = read_matrix("good_double_matrix.txt", " ,");
  MatrixXd expected(4,3);
  expected << 3.23, 1.34, 6.57, 8.15,
            1.37, -13.6, 456.3, 4.3,
            4, 4.2, 0, -1.234;
  EXPECT_EQ(M, expected);
}

TEST(TestReadMatrix, BadDoubleMatrix) {
  ASSERT_THROW(read_matrix("bad_double_matrix.txt", " ,"), SizeError);
}