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
 * @return A matrix with the selected columns
 * The template parameters are the the the type of the content of the matrix
 * (int, float, double, etc) and the container that stores the indices,
 * (std::vector, VectorXi, etc)
 */
template<class ContentType, typename ContainerType> 
Matrix<ContentType, Dynamic, Dynamic> select_columns(
                  const Matrix<ContentType, Dynamic, Dynamic> &m,
                  const ContainerType &indices) {
  unsigned int rows = m.rows();
  unsigned int n_indices = indices.size();
  Matrix<ContentType, Dynamic, Dynamic> result(rows, n_indices);
  
  for (unsigned int i=0, col=0; i < n_indices; ++i, ++col) {
    result.col(col) = m.col(indices[i]);
  }
  return result;
}


/**
 * Selects columns from a matrix
 * @param m Matrix
 * @param indices The columns to select (the container can be anything that 
 * supports the size() function and access to the elements with []
 * @param ContentType The type stored in the matrix (int, double, etc)
 * @return Returns a matrix containing only the rows selected
 */
template<class ContentType, typename ContainerType> 
Matrix<ContentType, Dynamic, Dynamic> select_rows(
                  const Matrix<ContentType, Dynamic, Dynamic> &m,
                  const ContainerType &indices) {
  if(indices.empty()) {
    return m;
  }
  unsigned int cols = m.cols();
  unsigned int n_indices = indices.size();
  Matrix<ContentType, Dynamic, Dynamic> result(n_indices, cols);
  for (unsigned int i=0, row=0; i < indices.size(); ++i, ++row) {
    result.row(row) = m.row(indices[i]);
  }
  return result;
}


#endif	/* EIGEN_HELPER_H */

