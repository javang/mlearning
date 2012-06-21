
#include "trees/RandomForest.h"
#include "utility/eigen_helper.h"
#include "algorithms/sample.h"
#include "utility/errors.h"
#include <stdexcept>
#include <random>


RandomForest::RandomForest(unsigned int n_trees) {
  n_trees_ = n_trees;
  set_information_measure(GINI);
}

void RandomForest::do_training(const MatrixXd &data,
            const VectorXi &classes,
            VariableTypes is_categorical) {
  Ints choices = get_random_sample(data.rows());
  for (unsigned int i = 0; i < n_trees_; ++i) {
    DecisionTreePtr ptr(new DecisionTree());
    ptr->set_information_measure(information_measure_);
    Ints choices = get_random_sample(data.rows());
    ptr->train(data, classes, is_categorical);
    trees_.push_back(ptr);
  }
}

VectorXi RandomForest::get_prediction(const MatrixXd &data) const {
  VectorXi classes(data.rows());
  for (std::size_t i = 0; i < data.rows(); ++i) {
    classes[i] = get_prediction_datapoint(data.row(i));
  }
  return classes;
}

int RandomForest::get_prediction_datapoint(const VectorXd &datapoint) const {
  check_empty();
  VectorXi predictions(n_trees_);
  for (unsigned int i = 0; i < trees_.size(); ++i) {
    predictions[i] = trees_[i]->predict_datapoint(datapoint);
  }
  IntPair p = mode(predictions);
  return p.first;
}

void RandomForest::check_empty() const {
  if(trees_.empty()) {
    throw SizeError("There are no trees in the forest");
  }
}
