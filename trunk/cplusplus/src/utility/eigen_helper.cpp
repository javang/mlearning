
#include "utility/eigen_helper.h"
#include "utility/errors.h"
#include <iostream>


MatrixXd divide_colwise(const MatrixXd &a, const MatrixXd &x) {
  if(x.cols() > 1 || x.rows() != a.rows()) {
    throw ValueError(
                    "divide_colwise: second argument has incorrect dimensions");
  }
  unsigned int cols = a.cols();
  unsigned int rows = a.rows();
  MatrixXd result(rows, cols);
  for (unsigned int i = 0; i < cols; ++i) {
    result.col(i).array() = a.col(i).array() / x.array(); 
  }
  return result;
}
