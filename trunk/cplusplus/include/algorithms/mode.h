/* 
 * File:   mode.h
 * Author: javi
 *
 * Created on May 6, 2012, 4:42 PM
 */

#ifndef MODE_H
#define	MODE_H

#include "definitions.h"


namespace ml {
namespace algorithms {


// IntPair mode(const Ints &values);


IntPair mode(const int *values, unsigned int size);

/**
 * Algorithm for the mode based on a hash table. The class T must support access
 * with the operator [] and the function size()
 * @param values A vector of integers
 * @return a pair (mode, counts)
 */
template<class T>
IntPair mode(const T &values) {
  Hash::iterator it;
  Hash hash;
  for (int i = 0; i < values.size(); i++) {
    it = hash.find(values[i]);
    if(it == hash.end()) {
      hash.insert( std::make_pair(values[i], 1));
    } else {
      it->second += 1;
    }
  }
  unsigned int counts = 0;
  Hash::iterator found;
  for (it = hash.begin(); it != hash.end(); ++it) {
    if(it->second > counts) {
      counts = it->second;
      found = it;
    }
  }
  return *found;
}

} // algorithms
} // ml

#endif	/* MODE_H */

