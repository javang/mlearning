/* 
 * File:   print_utils.h
 * Author: javi
 *
 * Created on May 11, 2012, 8:35 PM
 */

#ifndef PRINT_UTILS_H
#define	PRINT_UTILS_H

#include <ostream>

/**
  Print all the elements from the first iterator to the last iterator.
  @param first The first iterator
  @param last The last iterator
  @param out The stream used for printing the output
template<class InputIterator>
void print(InputIterator first, InputIterator last, std::ostream &out) {
  for(; first != last; first++ ) {
    out << *first << " ";
  }
  out << std::endl;
}

#endif	/* PRINT_UTILS_H */

