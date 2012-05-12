/* 
 * File:   print_utils.h
 * Author: javi
 *
 * Created on May 11, 2012, 8:35 PM
 */

#ifndef PRINT_UTILS_H
#define	PRINT_UTILS_H

#include <ostream>

template<class InputIterator>
void print(InputIterator first, InputIterator last, std::ostream &out) {
  for(; first != last; ++first ) {
    out << *first << " ";
  }
  out << std::endl;
}

#endif	/* PRINT_UTILS_H */

