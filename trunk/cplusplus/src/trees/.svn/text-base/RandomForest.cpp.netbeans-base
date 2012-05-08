
#include "trees/RandomForest.h"
#include "utility/eigen_helper.h"
#include "algorithms/sample.h"
#include <stdexcept>
#include <random>

RandomForest::RandomForest(unsigned int n_trees) {
  n_trees_ = n_trees;
  set_information_measure(GINI);
}

void RandomForest::train(const MatrixXd &data,
            const VectorXi &classes,
            VariableTypes is_categorical) {
  Ints choices = get_random_sample(data.rows());
  for (unsigned int i = 0; i < n_trees_; ++i) {
    DecisionTree T;
    T.set_information_measure(information_measure_);
    Ints choices = get_random_sample(data.rows());
    // TODO: Get a way of passing the selected sample without copying it
    T.train(data, classes, is_categorical);
    trees_.push_back(T);
  }
}

VectorXi RandomForest::predict(const MatrixXd &data) {
  MatrixXi predictions(data.rows(), n_trees_);
  if(trees_.size() == 0) {
    throw std::length_error("There are no trees in the forest");
  }
  for (unsigned int i = 0; i < trees_.size(); ++i) {
    VectorXi p = trees_[i].predict(data);
    predictions.col(i) = p;
  }
  VectorXi classes(data.rows());
  for (unsigned int i = 0; i < data.rows(); ++i) {
    VectorXi v = predictions.row(i);
    IntPair p = mode(v.data(), n_trees_);
  }
  return classes;
}

