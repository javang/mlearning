
#include "trees/DecisionNode.h"


bool DecisionNode::matches_value(double value, bool is_categorical) {
    if(is_categorical) {
        return static_cast<int>(value) == static_cast<int>(feature_value_);
    } else if(threshold_type_ == LOWER ) {
        return value <= feature_value_;
    } else if(threshold_type_ == HIGHER) {
        return value > feature_value_;
    } else {
        throw("Matches_value: wrong option. Check threshold_type value");
    }
}    

