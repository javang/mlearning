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
#include "definitions.h"

namespace ml {
namespace utility {
    

/**
 * Divides the array a by the array x 
 * @param a Matrix to divide
 * @param x Matrix dividing a (it must have only one column
 * @return  Matrix with the columns divided element-wise by x
 */
Eigen::MatrixXd divide_colwise(const Eigen::MatrixXd &a,
                                      const Eigen::MatrixXd &x);


/**
 * Selects columns from a matrix
 * @param m A Eigen Matrix
 * @param indices The columns to select (the container can be anything that 
 * supports the size() function and access to the elements with []
 * @return A matrix with the selected columns
 * The template parameters are the the the type of the content of the matrix
 * (int, float, double, etc) and the container that stores the indices,
 * (std::vector, Eigen::VectorXi, etc)
 */

template<class ContentType, typename ContainerType> 
Eigen::Matrix<ContentType, Eigen::Dynamic, Eigen::Dynamic> select_columns(
          const Eigen::Matrix<ContentType, Eigen::Dynamic, Eigen::Dynamic> &m,
          const ContainerType &indices) {
  unsigned int rows = m.rows();
  unsigned int n_indices = indices.size();
  Eigen::Matrix<ContentType, 
                Eigen::Dynamic, Eigen::Dynamic> result(rows, n_indices);
  
  for (unsigned int i=0, col=0; i < n_indices; ++i, ++col) {
    result.col(col) = m.col(indices[i]);
  }
  return result;
}


/**
 * Selects rows from a matrix
 * @param m Matrix
 * @param indices The columns to select (the container can be anything that 
 * supports the size() function and access to the elements with []
 * @param ContentType The type stored in the matrix (int, double, etc)
 * @return Returns a matrix containing only the rows selected
 */
template<class ContentType, typename ContainerType> 
Eigen::Matrix<ContentType, Eigen::Dynamic, Eigen::Dynamic> select_rows(
                  const Eigen::Matrix<ContentType, Eigen::Dynamic, Eigen::Dynamic> &m,
                  const ContainerType &indices) {
  if(indices.empty()) {
    return m;
  }
  unsigned int cols = m.cols();
  unsigned int n_indices = indices.size();
  Eigen::Matrix<ContentType, Eigen::Dynamic, Eigen::Dynamic> result(n_indices, cols);
  for (unsigned int i=0, row=0; i < indices.size(); ++i, ++row) {
    result.row(row) = m.row(indices[i]);
  }
  return result;
}

/**
 * Go through a column in the matrix and return the rows where the predicate
 * is true
 * @param data Matrix
 * @param column column to use
 * @param value value
 * @param Predicate => A class with a binary function
 * @return The rows that satisfy the predicate
 */
template<typename type, class Predicate>
Ints rows_where_true(const Eigen::MatrixXd &data, unsigned int column,
                         Predicate f) {
  Ints new_rows_to_use;
  for(unsigned int i = 0; i < data.rows(); i++) 
    if(f(data.cast<type>()(i,column)))
      new_rows_to_use.push_back(i);
  return new_rows_to_use;
};


} // utility
} // ml

#endif	/* EIGEN_HELPER_H */

