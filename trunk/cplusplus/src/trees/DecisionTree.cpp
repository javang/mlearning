
#include "trees/DecisionTree.h"
#include "trees/DecisionNode.h"
#include "algorithms/mode.h"
#include "definitions.h"
#include "utility/print_utils.h"
#include "algorithms/index_related.h"
#include "utility/eigen_helper.h"
#include "utility/errors.h"
#include <algorithm>
#include <functional>
#include <memory>
using namespace Eigen;
using namespace ml::algorithms;
using namespace ml::utility;        

namespace ml {
namespace trees {


void DecisionTree::do_training(const MatrixXd &data, const VectorXi &classes,
              VariableTypes variable_types) {
  columns_to_use_.resize(data.cols());
  std::fill(columns_to_use_.begin(), columns_to_use_.end(), true);
  variable_types_ = variable_types;
  DecisionNodePtr p(new DecisionNode());
  // Casting is neccessary because set_root expects a TreeNodePtr
  set_root(std::dynamic_pointer_cast<TreeNode>(p));
  get_tree(p, data, classes);
}


void DecisionTree::get_tree(DecisionNodePtr node,
                            const MatrixXd &data,
                            const VectorXi &classes) {
  
  IntsSet unique_classes(classes.data(), classes.data()+classes.size());
  if(unique_classes.size() == 1 || number_of_columns_in_use() == 1) {
    IntPair mode_pair = mode(classes.data(), classes.size());
    node->set_class(mode_pair.first);
  } else {
    // (gain, threshold, column for split)
    std::tuple<double, unsigned int, double> gain = get_best_gain(data, classes);
    double g  = std::get<0>(gain);
    double threshold = std::get<2>(gain);
    unsigned int column = std::get<1>(gain);
    node->set_column_for_next_split(column);
    columns_to_use_[column] = false;
    if(variable_types_[column] == CATEGORICAL) {
      IntsSet vals;
      for(unsigned int i = 0; i < data.rows(); i++) {
        vals.insert(data.cast<int>()(i,column));
      }
      for(auto value: vals) {
        DecisionNodePtr child(new DecisionNode());
        child->set_feature(column);
        child->set_feature_value(value);
        node->add_child(child);
        Ints new_rows_to_use = rows_where_true<int>(data, column,
                std::bind2nd(std::equal_to<int>(), value));
//        print(new_rows_to_use.begin(), new_rows_to_use.end(), std::cout);
        // TODO: Find a way of selecting rows without copying them 
        // (some sort of view?)
        MatrixXd new_data = select_rows<double, Ints>(data, new_rows_to_use);
        VectorXi new_classes = select_rows<int, Ints>(classes, new_rows_to_use);
        get_tree(child, new_data, new_classes);
      }
    // continuous feature  
    } else {
      std::vector<ThresholdType> types = {HIGHER, LOWER};
      for(auto type: types) {
        DecisionNodePtr child(new DecisionNode());
        child->set_feature(column);
        child->set_feature_value(threshold);
        child->set_threshold_type(type);
        node->add_child(child);
        Ints new_rows_to_use;
        if(type == LOWER) {
          new_rows_to_use = rows_where_true<double>(data, column,
                std::bind2nd(std::less_equal<double>(), threshold));
        } else if(type == HIGHER) {
          new_rows_to_use = rows_where_true<double>(data, column,
                std::bind2nd(std::greater<double>(), threshold));
        }
        MatrixXd new_data = select_rows<double, Ints>(data, new_rows_to_use);
        VectorXi new_classes = select_rows<int, Ints>(classes, new_rows_to_use);
        get_tree(child, new_data, new_classes);
      }
    }
  }
}  

unsigned int DecisionTree::number_of_columns_in_use() const {
  return std::count(columns_to_use_.begin(), columns_to_use_.end(), true);
}


VectorXi DecisionTree::get_prediction(const MatrixXd &data) const {
  VectorXi predictions = VectorXi::Zero(data.rows());
  for(std::size_t i = 0; i < data.rows(); i++) {
    DecisionNodePtr p = std::dynamic_pointer_cast<DecisionNode>(root_);
    predictions(i) =  get_prediction(p.get(), data.row(i));
  }
  return predictions;
}

int DecisionTree::get_prediction_datapoint(const VectorXd &data) const {
  DecisionNodePtr p = std::dynamic_pointer_cast<DecisionNode>(root_);
  int pred = get_prediction(p.get(), data);
  return pred;
}


int DecisionTree::get_prediction(DecisionNode *node, 
                            const VectorXd &data_point) const {
  int prediction = 0;
  if(node->is_leaf()) {
    return node->get_class();
  } else {
    unsigned int col = node->get_column_for_next_split();
    NodePtr child = node->get_first_child();
    while(child != 0) {
      // Recover a pointer to DecisionNode. It can be done because I know that
      // children are indeed DecisionNodes and the class TreeNode is polymorphic.
      // No need to delete (there is no memory allocation involved
      DecisionNodePtr ptr = std::dynamic_pointer_cast<DecisionNode>(child);
      if(ptr->matches_value(data_point(col), variable_types_[col])) {
        return get_prediction(ptr.get(), data_point);
      }   
      child = child->get_next_sibling();
    }
    throw ValueError("Value for the node not found in the tree");
  }
}

std::tuple<double, unsigned int, double>
  DecisionTree::get_best_gain(const MatrixXd &data, 
                              const VectorXi &classes) {
  // If best_gain == 0 and all the gains for the columns are 0, the 
  // best feature is always set to 0. Avoid it setting best-gain to -1
  double best_gain = -1; 
  double threshold = 0;
  double best_feature = 0;
  for(int i=0; i < columns_to_use_.size(); ++i) {
    if(columns_to_use_[i]) {
      GainPair g = information_gain(data.col(i), classes, variable_types_[i],
                                                         information_measure_);
      if(g.first > best_gain) { 
        best_gain = g.first;
        threshold = g.second;
        best_feature = i;
      }
    }
  }
  auto result = std::make_tuple(best_gain, best_feature, threshold);
  return result;
}
} // trees
} // ml