/* 
 * File:   eigen_helper.h
 * Author: javi
 *
 * Created on May 2, 2012, 10:22 PM
 */

#ifndef EIGEN_HELPER_H
#define	EIGEN_HELPER_H

#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

/**
 * Divides the array a by the array x 
 * @param a Matrix to divide
 * @param x Matrix dividing a (it must have only one column
 * @return  Matrix with the columns divided element-wise by x
 */
MatrixXd divide_colwise(const MatrixXd &a, const MatrixXd &x);


/**
 * Selects columns from a matrix
 * @param m A Eigen Matrix
 * @param indices The columns to select (the container can be anything that 
 * supports the size() function and access to the elements with []
 * @return 
 */
template<class ContentType, typename ContainerType> 
Matrix<ContentType, Dynamic, Dynamic> select_columns(
                  const Matrix<ContentType, Dynamic, Dynamic> &m,
                  const ContainerType &indices) {
  unsigned int rows = m.rows();
  unsigned int n_indices = indices.size();
  Matrix<ContentType, Dynamic, Dynamic> result(rows, n_indices);
  
  for(unsigned int i = 0; i < rows; i++) {
    for(unsigned int j = 0, col = 0; j < n_indices; ++j, ++col) {
      result(i,col) = m(i, indices[j]);
    }
  }
  return result;
}


#endif	/* EIGEN_HELPER_H */

