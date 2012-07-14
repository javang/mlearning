/* 
 * File:   index_related.h
 * Author: javi
 *
 * Created on May 9, 2012, 5:04 PM
 */

#ifndef INDEX_RELATED_H
#define	INDEX_RELATED_H

namespace ml {
namespace algorithms {


/**
 * @param Finds all the elements where the predicate is true
 * @param first First iterator
 * @param last Second iterator
 * @param pred Predicate used to evaluate the condition
 * @return a vector of iterators to elements where the condition is true
 */
template<class InputIterator, class Predicate>
std::vector<InputIterator>
find_all_if(InputIterator first, InputIterator last, Predicate pred) {
  std::vector<InputIterator> result;
  for ( ; first!=last ; first++ ) {
    if(pred(*first)) {
      result.push_back(first);
    }
  }
  return result;
}


/**
 * Computes the distance to the first iterator for the values that make the
 * predicate true
 * @param first First iterator
 * @param last Second iterator
 * @param pred predicate
 * Example: To get the indices of a vector where the value is 3:
     std::vector<int> indices = get_distances_if(v.begin(), v.end(),
 *                                    std::bind2nd(std::equal_to<int>(),3);
 */
template<class InputIterator , class Predicate>
Ints get_distances_if(InputIterator first, InputIterator last, Predicate pred) {
  Ints distances;
  InputIterator begin = first;
  for( ; first != last; ++first) {
    if( pred(*first)) distances.push_back( std::distance(begin, first ));
  }  
  return distances;
} 

} // algorithms
} // ml

#endif	/* INDEX_RELATED_H */

