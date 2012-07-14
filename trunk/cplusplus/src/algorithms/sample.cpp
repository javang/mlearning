
#include "algorithms/sample.h"
#include <random>
#include <algorithm>

namespace ml {
namespace algorithms {

Ints get_random_sample(unsigned long n_values) {
  Ints v(n_values);
  for (unsigned int i = 0; i < n_values; ++i) v[i] = i;
  std::random_shuffle(v.begin(), v.end());
  std::random_device rd;
  std::minstd_rand generator(rd());
  std::uniform_int_distribution<unsigned long> unif(1,n_values);
  unsigned long n_choices = unif(generator);
  v.erase(v.begin()+n_choices, v.end());
  return v; 
}


} // algorithms
} // ml
