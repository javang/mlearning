
#include "gtest/gtest.h"


#include "utility/eigen_helper.h"
#include "definitions.h"
#include "algorithms/argsort.h"
#include "algorithms/mode.h"
#include "algorithms/sample.h"
#include "algorithms/index_related.h"

#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include <functional>

using namespace ml;
using namespace ml::algorithms;
using namespace ml::utility;
using namespace Eigen;

TEST(TestAlgorithms, TestArgsort) {
  Doubles v;
  std::srand(time(nullptr));
  for (unsigned int i = 0; i <100; ++i) {
    v.push_back(std::rand());
  }
  Ints indices = argsort(v.begin(), v.end());
  for (unsigned int i = 1; i < indices.size(); ++i) {
    EXPECT_LE(v[indices[i-1]], v[indices[i]]);
  }
}

TEST(TestAlgorithms, TestArgsortEigen) {
  VectorXd v(6);
  v  << 1.0, 3, 4, 2.3, 11, 7.2;
  Ints indices = argsort<double>(v.data(), v.size());
  VectorXi expected(6);
  expected << 0, 3, 1, 2, 5, 4;
  for (unsigned int i = 0; i < indices.size(); ++i) {
    EXPECT_EQ(indices[i], expected[i]);
  }
}


TEST(TestAlgorithms, TestMode) {
  VectorXi v(20);
  v  << 1, 3, 4, 4, 2, 1, 9 , 4, 6, 7 , 2, 8, 8, 8, 9, 3, 3 , 1, 3, 5;
  IntPair p = mode(v.data(), v.size());
  EXPECT_EQ(p.first, 3);
  EXPECT_EQ(p.second, 4);
}

TEST(TestAlgorithms, TestGetRandomSample) {
  Ints choices = get_random_sample(20);
  EXPECT_LE(choices.size(), 20);
  // All the elements in choice must be different
  std::set<int> my_set(choices.begin(), choices.end());
  EXPECT_EQ(my_set.size(), choices.size());
}

TEST(TestAlgorithms, TestIndexRelated) {
  VectorXi v(6);
  v << 1, 2, 3, 3, 2, 3;
  Ints expected = { 2, 3, 5};
  Ints result = get_distances_if(v.data(),
                                 v.data() + v.size(),
                                 std::bind2nd(std::equal_to<int>(), 3)); 
  Ints  t = {1, 2, 3, 3, 2 ,3};
  Ints result2 = get_distances_if(t.begin(),
                                  t.end(),
                                  std::bind2nd(std::equal_to<int>(), 3)); 
  for(unsigned int i = 0; i < expected.size(); i++) {
    EXPECT_EQ(expected[i], result[i]);
    EXPECT_EQ(expected[i], result2[i]);
  }
}

TEST(TestAlgorithms, TestFindAllEqual) {
  VectorXi v(6);
  v << 1, 2, 3, 3, 2, 3;
  std::vector<int *> pointers;
  pointers = find_all_if<int *>(v.data(),
          v.data()+v.size(),
          std::bind2nd(std::equal_to<int>(), 3));
  // All the values referenced by the pointers must be equal to 3
  for(unsigned int i = 0; i < pointers.size(); i++) {
    EXPECT_EQ( *(pointers[i]), 3);
  }
}


TEST(TestAlgorithms, TestGetDistances) {
  VectorXi v(6);
  v << 1, 2, 3, 3, 2, 3;
  Ints indices = get_distances_if(v.data(),
                                  v.data()+v.size(),
                                  std::bind2nd(std::equal_to<int>(), 3));
  Ints expected = {2, 3 ,5};
  for(unsigned int i = 0; i < indices.size(); i++) {
    EXPECT_EQ(expected[i], indices[i] );
  }
  // double
  VectorXd w(6);
  w << 2.3, 4.5, 23.3, 1.2, 34.1, 12.1;
  Ints expected2 = {0,1,3};
  indices = get_distances_if(w.data(), w.data()+w.size(),
                                  std::bind2nd(std::less<double>(), 12));

  for(unsigned int i = 0; i < indices.size(); i++) {
    EXPECT_EQ(expected2[i], indices[i] );
  }

  indices = get_distances_if(w.data(), w.data()+w.size(),
                                  std::bind2nd(std::greater<double>(), 23));
  Ints expected3 = {2,4};
  for(unsigned int i = 0; i < indices.size(); i++) {
    EXPECT_EQ(expected3[i], indices[i] );
  }
}

