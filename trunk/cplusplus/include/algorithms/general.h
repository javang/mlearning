/* 
 * File:   general.h
 * Author: javi
 *
 * Created on July 12, 2012, 11:48 AM
 */

#ifndef GENERAL_H
#define	GENERAL_H

namespace ml {
namespace algorithms {

/**
 * Apply a function to the elements of a sequence if the predicate is true
 * @param first Beginning position
 * @param last Ending position
 * @param pred Predicate
 * @param f Function
 * @return 
 */
template< class InputIterator, class Function, class Predicate >
void for_each_if(InputIterator first, InputIterator last, 
                                        Predicate pred, Function f) {
  for( ; first != last; ++first) {
    if( pred(*first) ) f(*first);
  }  
}

} // algorithms
} // ml


#endif	/* GENERAL_H */

