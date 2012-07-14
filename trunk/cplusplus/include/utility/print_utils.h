/* 
 * File:   print_utils.h
 * Author: javi
 *
 * Created on May 11, 2012, 8:35 PM
 */

#ifndef PRINT_UTILS_H
#define	PRINT_UTILS_H

#include <ostream>

namespace ml {
namespace utility {

/**
 * Print the contents of a container that can be explored with an iterator
 * @param first First iterator
 * @param last Last iterator
 * @param out Output stream
 */
template<class InputIterator>
void print(InputIterator first, InputIterator last, std::ostream &out) {
  for(; first != last; first++ ) {
    out << *first << " ";
  }
  out << std::endl;
}

} // utility
} // ml

#endif	/* PRINT_UTILS_H */

