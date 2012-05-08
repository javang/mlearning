
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

  ThresholdType get_threshold_type() const {
    return threshold_type_;
  }
  void set_threshold_type(ThresholdType x) {
    threshold_type_ = x;
  }
  
  int get_column_for_next_split() const {
    return column_for_next_split_;
  }
  void set_column_for_next_split(unsigned int t) {
    column_for_next_split_ = t;
  }

  double get_feature_value() const {
    return feature_value_;
  }
  double set_feature_value(int t) {
    feature_value_ = t;
  }

  int get_feature() const {
    return feature_;
  }
  void set_feature(int t) {
    feature_ = t;
  }

  int get_class() const {
    return class_;
  }
  void get_class(unsigned int t) {
    class_ = t;
  }

  bool matches_value(double value, bool is_categorical);

};


typedef std::shared_ptr<DecisionNode> DecisionNodePtr;
typedef std::vector<DecisionNodePtr > DecisionNodePtrs;


#endif
