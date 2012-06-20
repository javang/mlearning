/* 
 * File:   argsort.h
 * Author: javi
 *
 * Created on May 4, 2012, 7:22 PM
 */

#ifndef ARGSORT_H
#define	ARGSORT_H

#include <algorithm>
#include "core/definitions.h"

template<class InputIterator>
class CompareWithIterators {
  const InputIterator it_;
public:

  /**
   * Prepares the class to compare
   * @param input The container whose elements are going to be compared
   */
  CompareWithIterators(const InputIterator &it ): it_(it) {}

  /**
   * Compares the elements i and j in the container used as input
   * @param i
   * @param j
   * @return True if the element i is lower than element j
   */
  bool operator()(int i, int j) {
    return *(it_+i) < *(it_+j);
  }
};

template<typename T>
class CompareWithPointers {
  const T *it_;
public:
  /**
   * @param a pointer to the first element of the vector to sort
   */
  CompareWithPointers(const T *input): it_(input) {}

  /**
   * Compares the elements i and j in the container used as input
   * Version that uses a pointer instead of an iterator
   * @param i
   * @param j
   * @return True if the element i is lower than element j
   */
  bool operator()(int i, int j) {
    return *(it_+i) < *(it_+j);
  }
};



/**
 * Performs an argsort for the elements between the iterator
 * @param first Iterator to the first element 
 * @param last Iterator to the last element 
 * @return The indices that sort the elements of "values" in ascending order
 */
template<class InputIterator>
Ints argsort(InputIterator first, InputIterator last) {
  unsigned int size = std::distance(first, last);
  Ints indices(size);
  CompareWithIterators<InputIterator> compare(first);
  std::sort(indices.begin(),indices.end(), compare);  
  return indices;
}



/**
 * Performs an argsort
 * @param values A pointer to a vector of values
 * @param size The number of values in the vector
 * @return The indices that sort the elements of "values" in ascending order
 */
template <typename T>
Ints argsort(const T *values, unsigned int size) {
  Ints indices_(size);
  for( int i = 0; i < size; ++i ) indices_[i] = i;
  CompareWithPointers<T> compare(values);
  std::sort(indices_.begin(),indices_.end(), compare);  
  return indices_;
}



#endif	/* ARGSORT_H */

