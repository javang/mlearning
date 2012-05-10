
#include "trees/DecisionTree.h"
#include "trees/information_gain.h"
#include "algorithms/mode.h"
#include <algorithm>
#include <functional>

void DecisionTree::train(const MatrixXd &data, const VectorXi &classes,
              Bools is_categorical) {
  std::fill(columns_in_use_.begin(), columns_in_use_.end(), true);
  is_categorical_ = is_categorical;
  root_ = DecisionNodePtr(new DecisionNode());
  get_tree(root_, data, classes);
}

VectorXi DecisionTree::predict(const MatrixXd &data) const {
  VectorXi predictions = VectorXi::Zero(data.rows());
  for(unsigned int i = 0; i < data.rows(); i++) {
    predictions(i) =  get_prediction(root_, data.row(i));
  }
  return predictions;
}

void DecisionTree::get_tree(DecisionNodePtr node,
                            const MatrixXd &data,
                            const VectorXi & classes, 
                            const Ints &rows_to_use) {
  IntsSet unique_classes(classes.data(), classes.data()+classes.size());
  if(unique_classes.size() == 1 || number_of_colums_in_use() == 1) {
    unsigned int cl = mode(classes.data(), classes.size());
    node->set_class(cl);
  } else {
    // (gain, threshold, column for split)
    std::tuple<double, double, unsigned int> gain = get_best_gain(data,
                                                             classes,
                                                             rows_to_use);
    unsigned int column = std::get<2>(gain);
    node->set_column_for_next_split(column);
    columns_in_use_[column] = false;
    Ints new_rows_to_use;
    
    // Comparers
    std::equal_to<int> EqualInt;
    std::less<double> LessDouble;
    std::greater<double> GreaterDouble;
    
    if(is_categorical_[column]) {
      // unique values present in the column
      int *p = data.col(column).cast<int>.data();
      IntsSet vals(p, p+data.rows());
      for(auto value: vals) {
        DecisionNodePtr child(new DecisionNode());
        child->set_feature(column);
        child->set_feature_value(value);
        node->add_child(child);
        // Get all the indices of the elements in data.col(column) 
        // that are equal to the value
        // Twisted but general, because it can be applied below for thresholds
        std::binder2nd < EqualInt > Comparer(EqualInt(), value);
        // Indices of the rows to use for the subtree
        int *init = data.col(column).cast<int>.data();
        new_rows_to_use = get_distances_if(init, init + data.rows(), Comparer);
        get_tree(child, selected_data, selected_classes, new_rows_to_use);
      }
    // continuous feature  
    } else {
      std::vector<ThresholdType> types = {HIGHER, LOWER};
      for(auto type: types) {
        double threshold = std::get<1>(gain);
        DecisionNodePtr child(new DecisionNode);
        child->set_feature(column);
        child->set_feature_value(type);
        node->add_child(child);
        if(type == LOWER) {
          std::binder2nd < LessDouble > Comparer(LessDouble(), threshold);
        } else if(type == HIGHER) {
          std::binder2nd < GreaterDouble > Comparer(GreaterDouble(), threshold);          
        }
        double *init = data.col(column).data();
        // Indices of values where the comparison is true (lower of greater)
        new_rows_to_use = get_distances_if(init, init + data.rows(), Comparer);
        get_tree(child, data, classes, new_rows_to_use);
      }
    }
  }
}  

unsigned int DecisionTree::number_of_columns_in_use() const {
  return std::count(columns_in_use_.begin(), columns_in_use_.end(), true);
}

unsigned int DecisionTree::get_prediction(const DecisionNodePtr &node, 
                            const VectorXd &data_point) const {
  unsigned int prediction = 0;
  if(node->is_leaf()) {
    prediction = node->get_class();
    return prediction;
  } else {
    unsigned int col = node->get_column_for_next_split();
    double val = data_point(col);
    DecisionNodePtrs children = node->get_children();
    for(auto child: node->get_children()) {
      if(child->matches_value(val, is_categorical_) ) {
        prediction = get_prediction(child, data_point);
        return prediction;
      }
    }
    throw ValueError("Value for the node not found in the tree");
  }
}

std::tuple<double, double, int>
  DecisionTree::get_best_gain(const MatrixXd &data, 
                              const VectorXi &classes,
                              const Ints &indices_to_use) {
  double best_gain = 0;
  double threshold = 0;
  double best_feature = 0;
  for(int i = 0; i < columns_in_use_.size(); i++) {
    if(colums_in_use_(i)) {
      GainPair g = information_gain(data.col(i), classes, is_categorical(i),
                                    information_measure_);
      if(g.first > best_gain) { 
        best_gain = g.first;
        threshold = g.second;
        best_feature = i;
      }
    }
  }
  auto result = std::make_tuple(best.gain, threshold, best_feature);
  return result;
}

