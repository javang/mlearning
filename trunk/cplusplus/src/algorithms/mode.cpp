
#include "algorithms/mode.h"
#include <unordered_map>

IntPair mode(const int *values, unsigned int size) {
  Hash::iterator it;
  Hash hash;
  for (int i = 0; i < size; i++) {
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

