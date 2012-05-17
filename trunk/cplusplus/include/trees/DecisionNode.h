
#ifndef DECISION_NODE_H
#define DECISION_NODE_H

#include "trees/TreeNode.h"
#include "trees/information_gain.h"
#include <vector>
#include <iostream>
#include <memory.h>

class DecisionNode: public TreeNode {

protected:
  unsigned int column_for_next_split_;
  double feature_value_;
  int feature_;
  ThresholdType threshold_type_;
  unsigned int class_;

public:

  /**
   * @return get the threshold type used by this node
   */
  ThresholdType get_threshold_type() const {
    return threshold_type_;
  }
  
  /**
   * Set the threshold type
   * @param x HIGHER or LOWER
   */
  void set_threshold_type(ThresholdType x) {
    threshold_type_ = x;
  }
  
  /**
   * 
   * @return The column that should be used for the next split in the tree
   * after using this node for prediction
   */
  int get_column_for_next_split() const {
    return column_for_next_split_;
  }
  
  /**
   * Set the column for the next split during training
   * @param t
   */
  void set_column_for_next_split(unsigned int t) {
    column_for_next_split_ = t;
  }

  /**
   * 
   * @return The value of the feature stored by the node
   */
  double get_feature_value() const {
    return feature_value_;
  }
  
  /**
   * 
   * @param t The value of the feature stored by the node
   * @return 
   */
  double set_feature_value(int t) {
    feature_value_ = t;
  }

  /**
   * 
   * @return The column containing the feature represented by the node
   */
  int get_feature() const {
    return feature_;
  }
  
  /**
   * 
   * @param t The column containing the feature represented by the node
   */
  void set_feature(int t) {
    feature_ = t;
  }

  /**
   * @return The value of the class for this node
   */
  int get_class() const {
    return class_;
  }
  
  /**
   * 
   * @param t The value of the class for this node
   */
  void set_class(unsigned int t) {
    class_ = t;
  }

  /**
   * Returns true if the value for the feature matches the value stored in the
   * node. 
   * @param value A value for a feature
   * @param vtype The type of the variable CATEGORICAL or CONTINUOUS
   * @return true or false
   */
  bool matches_value(double value, VariableType vtype);

};


typedef std::shared_ptr<DecisionNode> DecisionNodePtr;
typedef std::vector<DecisionNodePtr > DecisionNodePtrs;


#endif
