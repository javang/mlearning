
#include "trees/DecisionTree.h"
#include "trees/information_gain.h"
#include <algorithm>

void DecisionTree::train(const MatrixXd &data, const VectorXi &classes,
              Bools is_categorical) {
  std::fill(columns_in_use_.begin(), columns_in_use_.end(), true);
  is_categorical_ = is_categorical;
  root_ = DecisionNodePtr(new DecisionNode());
  get_tree(root_, data, classes);
}

VectorXdi DecisionTree::predict(const MatrixXd &data) const {
  VectorXi predictions = VectorXi::Zero(data.rows());
  for(unsigned int i = 0; i < data.rows(); i++) {
    predictions(i) =  get_precition(root_, data.row(i));
  }
  return predictions;
}

void DecisionTree::get_tree(DecisionNodePtr node,
                            const MatrixXd &data,
                            const VectorXi & classes) {
  IntsSet unique_classes(classes.data(), classes.data()+classes.size());
  if(unique_classes.size() == 1 || number_of_colums_in_use() == 1) {
    unsigned int cl = mode(classes.data(), classes.size());
    node->set_class(cl);
  } else {
    // (gain, threshold, column for split)
    tuple<double, double, unsigned int> gain = get_best_gain(data, classes);
    unsigned int column = std::get<2>(gain);
    node->set_column_for_next_split( column);
    columns_in_use_[column] = false;
    if(is_categorical[column]) {
      // unique values present in the column
      int *p = data.col(column).cast<int>.data();
      IntsSet vals(p, p+data.rows());
      for(int i = 0; i < vals.size(); i++) {
        MatrixXd selected_data;
        VectorXi selected_classes;
        get_matrices_for_value(data, classes, column, vals[i],
                               selected_data, selected_classes);
        DecisionNodePtr child(new DecisionNode());
        child->set_feature(column);
        child->set_feature_value(values[i]);
        node->add_child(child);
      get_tree(child, Z, W);
      }
    // continuous feature  
    } else {
      std::vector<ThresholdType> h = {HIGHER, LOWER};
      for(int i = 0; i < 2; i++) {
        double threshold = std::get<1>(gain);
        Z, W = get_matrices_for_threshold(data, classes, column, threshold,
                                          h[i])
        DecisionNodePtr child(new DecisionNode);
        child->set_feature(column);
        child->set_feature_value(h[i]);
        node->add_child(child);
        get_tree(child, Z, W);
      }
    }
  }
}  

unsigned int DecisionTree::number_of_columns_in_use() const {
  return std::count(columns_in_use_.begin(), columns_in_use_.end(), true);
}

unsigned int DecisionTree::get_prediction(const DecisionNodePtr &node, 
                            const VectorXd &data_point) {
  unsigned int prediction = 0;
  if(node->is_leaf()) {
    prediction = node->get_class();
    return prediction;
  } else {
    unsigned int col = node->get_column_for_next_split();
    double val = data_point(col);
    DecisionNodePtrs children = node->get_children();
    for(unsigned int i = 0; i < node->get_number_of_children(); i++) {
      if(children[i]->matches_value(vak, is_categorical_) ) {
        prediction = get_prediction(children[i], data_point);
        return prediction;
      }
    }
    throw ValueError("Value for the node not found in the tree");
  }
}

std::tuple<double, double, int> get_best_gain(const MatrixXd &data, 
                                              const VectorXi &classes) {
  double best_gain = 0;
  double threshold = 0;
  double best_feature = 0;
  for(int i = 0; i < columns_in_use_.size(); i++) {
    GainPair g = information_gain(data.col(i), classes, is_categorical(i),
                                  information_measure_);
    if(g.first > best_gain) {
      best_gain = g.first;
      threshold = g.second;
      best_feature = i;
    }
  }
  auto result = std::make_tuple(best.gain, threshold, best_feature);
  return result;

}

void get_matrices_for_value(const MatrixXd &data, const MatrixXd &classes,
                            unsigned int column, int value,
                            MatrixXd &selected_data, 
                            VectorXi &selected_classes) {
  /*
   
       function [Z, W] = get_matrices_for_value(X, Y, column, value)
        indices = (X(:, column) == value);
        Z = X(indices, :);
        W = Y(indices, :);
   */
}
