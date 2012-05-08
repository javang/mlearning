
#include "trees/DecisionTree.h"
#include <algorithm>

void DecisionTree::train(const MatrixXd &data, const VectorXi &classes,
              Bools is_categorical) {
  std::fill(columns_in_use_.begin(), columns_in_use_.end(), true);
  is_categorical_ = is_categorical;
  root_ = DecisionNodePtr(new DecisionNode());
  get_tree(root_, data, classes);
}

VectorXdi DecisionTree::predict(const MatrixXd &data) const {
  VectorXdi v;
  return v;
}

void DecisionTree::get_tree(DecisionNodePtr node,
                            const MatrixXd &data,
                            const VectorXi & classes) {
  IntsSet unique_classes(classes.data(), classes.data()+classes.size());
  if(unique_classes.size() == 1 || number_of_colums_in_use() == 1) {
    node->set_class( get_class(data) );
  } else {
    // (gain, threshold, column for split)
    tuple<double, double, unsigned int > gain = get_best_gain(data, classes);
    unsigned int column = std::get<2>(gain);
    node->set_column_for_next_split( column);
    columns_in_use_[column] = false;
    if(is_categorical[column]) {
      // unique values present in the column
      int *p = data.col(column).cast<int>.data();
      IntsSet vals(p, p+data.rows());
      for(int i = 0; i < vals.size(); i++) {
        Z, W = get_matrices_for_value(data, classes, column, vals[i]);
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
  return 0;
}

std::tuple<double, double, int> get_best_gain(const MatrixXd &data, 
                                              const VectorXi &data) {
  
}