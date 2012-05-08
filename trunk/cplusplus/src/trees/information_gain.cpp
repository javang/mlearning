#include "trees/information_gain.h"
#include "algorithms/argsort.h"
#include "utility/errors.h"
#include "utility/definitions.h"

#include <limits>
#include <iostream>
#include <cmath>

GainPair information_gain(const VectorXd &values, const VectorXi &classes, 
                        const VariableType &is_categorical,
                        const InformationMeasure &measure) {
  double gain = 0;
  double threshold = 0;
  GainPair gain_pair;
  if(measure == GINI) {
    if(is_categorical) {
      gain = nominal_gini_gain(values.cast<int>(), classes);
      gain_pair = std::make_pair(gain,0);
    } else {
      gain_pair = continuous_gini_gain(values, classes);
    }    
  } else if( measure == ENTROPY) {
    if(is_categorical) {
      gain = nominal_entropy_gain(values.cast<int>(), classes);
      gain_pair = std::make_pair(gain,0);
    } else {
      gain_pair = continuous_entropy_gain(values , classes);
    }
  }
  return gain_pair;
}


double nominal_gini_gain(const VectorXi &values, const VectorXi &classes) {
  MatrixXi T = get_cross_table(values, classes);
  // total_per_value(k) is the number of times that value k appears
  MatrixXi total_per_value = T.rowwise().sum(); 
  VectorXd probability_of_value = total_per_value.cast<double>() /values.rows();
  // Fraction of each class  per value
  MatrixXd fractions_yx = divide_colwise( T.cast<double>(),
                                          total_per_value.cast<double>());
  // Gini impurity for each value: sum fractions^2 over the rows
  VectorXd G = fractions_yx.array().square().rowwise().sum();
  double total_gini =  1 - probability_of_value.transpose() * G;
  VectorXi counts = T.colwise().sum();
  double gain = gini(counts.cast<double>()) - total_gini;
  return gain;
}

GainPair continuous_gini_gain(const VectorXd &values, const VectorXi &classes) {
  IntsSet unique_classes(classes.data(),classes.data() + classes.size()); 
  if(unique_classes.size() == 1) return std::make_pair(0, 0);

  VectorXi lower_contingency_table = VectorXi::Zero(unique_classes.size());
  // upper_contingency_table are the counts for each class
  VectorXi upper_contingency_table = get_cross_table(classes);
  double total_gini = gini(upper_contingency_table.cast<double>());
  double best_gain = 0;
  double best_threshold = 0;
  
  Ints indices = argsort<double>(values.data(), values.size());
  IntsSet::iterator begin = unique_classes.begin();  
  unsigned int n_classes = classes.size();
  // Scan the classes in the order obtained from sorting the values
  for (unsigned int i = 0; i < n_classes; ++i) {
    int current_class = classes[indices[i]]; // 
    IntsSet::iterator it = unique_classes.find(current_class);  
    unsigned int position = std::distance(begin, it); 
    lower_contingency_table(position) += 1;
    upper_contingency_table(position) -= 1;
    double P_low = 1. * i / n_classes;
    double G_low = gini(lower_contingency_table.cast<double>());
    double P_upp = 1. * (n_classes - i) / n_classes;
    double G_upp = gini(upper_contingency_table.cast<double>());
    double G = P_low * G_low + P_upp * G_upp;
    double g = total_gini - G;
    if(g > best_gain) {
      best_gain = g;
      best_threshold = values[indices[i]];
    }
  }
  return std::make_pair(best_gain, best_threshold);
}
       

double nominal_entropy_gain(const VectorXi &values, const VectorXi &classes) {
  MatrixXi T = get_cross_table(values, classes);
  MatrixXi total_per_value = T.rowwise().sum(); 
  VectorXd probability_of_value = total_per_value.cast<double>() /values.rows();
  MatrixXd fractions_yx = divide_colwise( T.cast<double>(),
                                          total_per_value.cast<double>());
  double epsilon = std::numeric_limits<double>::epsilon();
  double invlog = 1 / std::log(2);
  MatrixXd H = (- invlog) * fractions_yx.array() * 
                             (fractions_yx.array() + epsilon).log().array();
  double total_entropy = probability_of_value.transpose() * H.rowwise().sum();
  VectorXi counts = T.colwise().sum();
  double gain = entropy(counts.cast<double>()) - total_entropy;
  return gain;
}
  

GainPair continuous_entropy_gain(const VectorXd &values,
                                  const VectorXi &classes) {
  IntsSet unique_classes(classes.data(),classes.data() + classes.size()); 
  if(unique_classes.size() == 1) return std::make_pair(0, 0);
  VectorXi lower_contingency_table = VectorXi::Zero(unique_classes.size());
  // upper_contingency_table are the counts for each class
  VectorXi upper_contingency_table = get_cross_table(classes);
  double total_entropy = entropy(upper_contingency_table.cast<double>());
  double best_gain = 0;
  double best_threshold = 0;
  Ints indices = argsort<double>(values.data(), values.size());
  IntsSet::iterator begin = unique_classes.begin();  
  unsigned int n_classes = classes.size();

  for (unsigned int i = 0; i < n_classes; ++i) {
    int current_class = classes[indices[i]]; // 
    IntsSet::iterator it = unique_classes.find(current_class);  
    unsigned int position = std::distance(begin, it); 
    lower_contingency_table(position) += 1;
    upper_contingency_table(position) -= 1;
    double P_low = 1. * i / n_classes;
    double H_low = entropy(lower_contingency_table.cast<double>());
    double P_upp = 1. * (n_classes - i) / n_classes;
    double H_upp = entropy(upper_contingency_table.cast<double>());
    double H = P_low * H_low + P_upp * H_upp;
    double h = total_entropy - H;
    if(h > best_gain) {
      best_gain = h;
      best_threshold = values[indices[i]];
    }
  }
  return std::make_pair(best_gain, best_threshold);
}


MatrixXi get_cross_table(const VectorXi &values, const VectorXi &classes) {
  if(classes.rows() != values.rows()) {
    throw ValueError("The vector of classes and values do not have same size"); 
  }
  IntsSet vals(values.data(), values.data() + values.size());
  IntsSet cls(classes.data(), classes.data() + classes.size());
  MatrixXi cross_table = MatrixXi::Zero(vals.size(), cls.size());
  IntsSet::const_iterator cls_begin = cls.begin();
  IntsSet::const_iterator val_begin = vals.begin();
  IntsSet::iterator class_it;
  IntsSet::iterator value_it;
  for (int i = 0; i < classes.size(); ++i) {
    class_it  = cls.find( classes(i));
    value_it = vals.find(values(i));
    unsigned int j = std::distance(val_begin, value_it); 
    unsigned int k = std::distance(cls_begin, class_it); 
    cross_table(j, k) += 1;
  }
  return cross_table;
}

VectorXi get_cross_table(const VectorXi &values) {
  IntsSet vals(values.data(), values.data() + values.size());
  VectorXi cross_table = VectorXi::Zero(vals.size());
  IntsSet::const_iterator val_begin = vals.begin();
  IntsSet::iterator value_it;
  for (int i = 0; i < values.size(); ++i) {
    value_it = vals.find(values(i));
    unsigned int j = std::distance(val_begin, value_it); 
    cross_table(j) += 1;
  }
  return cross_table;
}


double gini(const VectorXd &values) {
  double sum = values.sum();
  VectorXd fy = values / sum;
  double g = 1 - fy.array().square().sum();
  return g;
}

double entropy(const VectorXd &values) {
  MatrixXd fy = values.array() / values.sum();
  double invlog = 1 / std::log(2);
  double epsilon = std::numeric_limits<double>::epsilon();
  // h = sum(fy * log2(fy+epsilon))
  double h =  (fy.array() * (fy.array() + epsilon).log().array() * invlog).sum();
  return (-1) * h;
}

