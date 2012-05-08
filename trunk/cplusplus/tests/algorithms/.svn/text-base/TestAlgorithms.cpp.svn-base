
#include "gtest/gtest.h"
#include "algorithms/argsort.h"
#include "algorithms/mode.h"
#include "algorithms/sample.h"

#include "utility/eigen_helper.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>

TEST(TestAlgorithms, TestArgsort) {
  std::vector<double> v;
  std::srand(time(NULL));
  for (unsigned int i = 0; i <100; ++i) {
    v.push_back(std::rand());
  }
  Ints indices = argsort< std::vector<double> >(v);
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
