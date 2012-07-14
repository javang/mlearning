
#include "trees/DecisionNode.h"
using namespace ml;
using namespace ml::trees;

bool DecisionNode::matches_value(double value, VariableType vtype) {
    if(vtype == CATEGORICAL) {
        return static_cast<int>(value) == static_cast<int>(feature_value_);
    } else if(threshold_type_ == LOWER ) {
        return value <= feature_value_;
    } else if(threshold_type_ == HIGHER) {
        return value > feature_value_;
    } else {
        throw("Matches_value: wrong option. Check threshold_type value");
    }
}    

