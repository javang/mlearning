
#include "trees/DecisionTree.h"
#include "trees/DecisionNode.h"
#include "algorithms/mode.h"
#include "utility/definitions.h"
#include "algorithms/index_related.h"
#include <algorithm>
#include <functional>
#include "boost/bind.hpp"

void DecisionTree::train(const MatrixXd &data, const VectorXi &classes,
              VariableTypes variable_types) {
  std::fill(columns_in_use_.begin(), columns_in_use_.end(), true);
  variable_types_ = variable_types;
  root_ = DecisionNodePtr(new DecisionNode());
  get_tree(root_, data, classes);
}

VectorXi DecisionTree::predict(const MatrixXd &data) const {
  VectorXi predictions = VectorXi::Zero(data.rows());
  for(unsigned int i = 0; i < data.rows(); i++) {
    predictions(i) =  get_prediction(root_.get(), data.row(i));
  }
  return predictions;
}

void DecisionTree::get_tree(DecisionNodePtr node,
                            const MatrixXd &data,
                            const VectorXi & classes, 
                            const Ints &rows_to_use) {
  IntsSet unique_classes(classes.data(), classes.data()+classes.size());
  if(unique_classes.size() == 1 || number_of_columns_in_use() == 1) {
    IntPair mode_pair = mode(classes.data(), classes.size());
    node->set_class(mode_pair.first);
  } else {
    // (gain, threshold, column for split)
    std::tuple<double, double, unsigned int> gain = get_best_gain(data,
                                                             classes,
                                                             rows_to_use);
    unsigned int column = std::get<2>(gain);
    node->set_column_for_next_split(column);
    columns_in_use_[column] = false;
    Ints new_rows_to_use;
    if(variable_types_[column]) {
      // unique values present in the column
      IntsSet vals;
      for(unsigned int i = 0; i < data.rows(); i++) {
        vals.insert(data.cast<int>()(i,column));
      }
      for(auto value: vals) {
        DecisionNodePtr child(new DecisionNode());
        child->set_feature(column);
        child->set_feature_value(value);
        node->add_child(child);
        // new_rows_to_use == > all the indices of the elements in 
        // data.col(column) that are equal to the value
        new_rows_to_use = get_distances_if(data.col(column).data(), data.col(column).data() + data.rows(),
                                    std::bind2nd(std::equal_to<int>(), value)); ///////////////// Problemas casi fijo. data es doubles y quiero avanzar con punteros sobre ints
        get_tree(child, data, classes, new_rows_to_use);
      }
    // continuous feature  
    } else {
      std::vector<ThresholdType> types = {HIGHER, LOWER};
      for(auto type: types) {
        double threshold = std::get<1>(gain);
        DecisionNodePtr child(new DecisionNode());
        child->set_feature(column);
        child->set_feature_value(type);
        node->add_child(child);
        const MatrixXd::Scalar *init = data.col(column).data();
        const MatrixXd::Scalar *end =  init + data.rows();
        if(type == LOWER) {
          new_rows_to_use = get_distances_if(init, end,
                           std::bind2nd(std::less<double>(), threshold));
        } else if(type == HIGHER) {
          new_rows_to_use = get_distances_if(init, end, 
                           std::bind2nd(std::greater<double>(), threshold));
        }
        get_tree(child, data, classes, new_rows_to_use);
      }
    }
  }
}  

unsigned int DecisionTree::number_of_columns_in_use() const {
  return std::count(columns_in_use_.begin(), columns_in_use_.end(), true);
}

unsigned int DecisionTree::get_prediction(DecisionNode *node, 
                            const VectorXd &data_point) const {
  unsigned int prediction = 0;
  if(node->is_leaf()) {
    prediction = node->get_class();
    return prediction;
  } else {
    unsigned int col = node->get_column_for_next_split();
    TreeNodePtr child = node->get_first_child();
    unsigned int child_i = 0;
    while(child != 0) {
      // Recover a pointer to DecisionNode. It can be done because I know that
      // children are indeed DecisionNodes and the class TreeNode is polymorphic.
      // No need to delete (there is no memory allocation involved
      DecisionNode *ptr = dynamic_cast<DecisionNode *>(child.get());
      if(ptr->matches_value(data_point(col), variable_types_[col])) {
        return get_prediction(ptr, data_point);
      }   
      child = child->get_next_sibling();
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
    if(columns_in_use_[i]) {
      GainPair g = information_gain(data.col(i), classes, variable_types_[i],
                                    information_measure_);
      if(g.first > best_gain) { 
        best_gain = g.first;
        threshold = g.second;
        best_feature = i;
      }
    }
  }
  auto result = std::make_tuple(best_gain, threshold, best_feature);
  return result;
}

