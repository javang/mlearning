

#ifndef INFORMATION_GAIN_H
#define INFORMATION_GAIN_H

#include "utility/eigen_helper.h"
#include "utility/definitions.h"
#include <utility>
#include <set>
#include <vector>

enum InformationMeasure {
  GINI, ENTROPY
};

std::vector<InformationMeasure> InformationMeasures;

enum ThresholdType {
  LOWER, HIGHER
};

enum VariableType {
  CATEGORICAL, CONTINUOUS
};
std::vector<VariableType> VariableTypes;



typedef std::pair<double, double> GainPair; // (gain, threshold)



//! Computes the information gain
/**
 * @param [in] classes A vector of ints identifying the classes of the
 *             values
 * @param [in] values The vector of values used to compute the information
 * gain
 * @param [in] is_categorical Identifies if values contains a categorical
 * variable
 * @param [in] measure The information measure used. GINI or ENTROPY
 * \return The function returns a pair (gain, threshold)
 
 */
GainPair information_gain(const VectorXd &values, const VectorXi &classes,
        const VariableType &is_categorical,
        const InformationMeasure &measure);


//! Computes the Gini information gain for a set of values given their 
//! classes Y
/**
 *   gain(classes|values) = G(Y) - sum_j ( P(xj) * G(Y|xj) )
 *   where:
 *   G(classes) is the total_gini impurity = 1 - sum_k( fy^2)   
 *   G(classes|value_j) - gini impurity calculated over the classes 
 *             corresponding to value_j
 *   fy = Fraction of class y within the classes
 *   P(value_j) = Probability of value xj in "values", estimated as fraction.
 * @param classes A vector ints identifying the classes for the values 
 * @param values 
 * @return a gain pair  
 */
double nominal_gini_gain(const VectorXi &values, const VectorXi &classes);

/**
 * Information gain according to the Gini impurity for a continuous variable X.
 * The function finds the threshold (t)  that produces the best split gain 
 *             gain = G(Y) - ( P(X<T) G(Y|X<t) + P(X>T) G(Y|X<t) )
 * @param values A column vector with values of X
 * @param classes A column vector with the classes for the values
 * @return A pair of values (gain, threshold)
 */
GainPair continuous_gini_gain(const VectorXd &values, const VectorXi &classes);



/**
 * Shannon's entropy gain for a nominal variable:
 * gain(classes|values) = H(classes) - sum_j ( P(value_j) * H(classes|value_j) )
 * where:
 *        H(Y) = log2(fy) * fy  --> fy = fraction of values of Y with class y  
          P(value_j) = Probability of value_j  (estimated as fraction).
          H(classes|value_j) - Entropy of the classes given value_j
    
 * @param values
 * @param classes
 * @return 
 */
double nominal_entropy_gain(const VectorXi &values, const VectorXi &classes);

GainPair continuous_entropy_gain(const VectorXd &values,
                                 const VectorXi &classes);


/** Computes the cross table T
 *  The element T(i,j) is the number of times that value i belongs to class j
 * the table has rows = number of values, cols = number of classes
 * @param classes
 * @param values
 * @return the cross table
 */
MatrixXi get_cross_table(const VectorXi &values, const VectorXi &classes);

/**
 * Cross table in 1D. It is equivalent to a histogram
 * @param values
 * @return The number of times that each value appears
 */
VectorXi get_cross_table(const VectorXi &values);

/**
 * Computes the gini impurity for a set of values
 * @param values
 * @return The value of the gini impurity
 */
double gini(const VectorXd &values);

/**
 * Computes the Shannon's entropy of a set of values
 * @param values
 * @return the value of the entropy
 */
double entropy(const VectorXd &values);




#endif

