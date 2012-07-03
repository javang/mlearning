/* 
 * File:   RandomForest.h
 * Author: javi
 *
 * Created on May 6, 2012, 2:16 PM
 */

#ifndef RANDOMFOREST_H
#define	RANDOMFOREST_H

#include "trees/information_gain.h"
#include "trees/DecisionTree.h"
#include "utility/eigen_helper.h"
#include "algorithms/mode.h"
#include "trees/Tree.h"
#include "core/types.h"

class RandomForest: public SupervisedClassifier {
private:
    /**
   * Train a number of decision trees. Each tree is trained with a random set 
   * of  data points
   * @param data A matrix of values for all the features. Rows are data points.
   *            and columns are features
   * @param classes The class for each data point.
   * @param is_categorical A vector with the type of each of the features
   */
  void do_training(const MatrixXd &data,
              const VectorXi &classes,
              VariableTypes is_categorical);
  
      /**
   * predicts the class of the data points in data.
   *  
   * @param data A matrix of values for all the features. Rows are data points.
   *            and columns are features
   * @return A vector with the class for each data point.
   */
  VectorXi get_prediction(const MatrixXd &data) const;

  int get_prediction_datapoint(const VectorXd &datapoint) const;
  
  /**
   * Check that the forest has trees
   */
  void check_empty() const;

  protected:
  DecisionTreePtrs trees_;
  InformationMeasure information_measure_;
  unsigned int n_trees_;

  
//  function choices = get_random_set(n_points);
//    n_choices = ceil(rand(1) * n_points);
//    choices = ceil( n_choices * rand(n_choices, 1));

public:
  RandomForest(unsigned int n_trees);

  /**
   * Sets the information measure used for classification
   * @param information_measure
   */
  void set_information_measure(InformationMeasure information_measure) {
    this->information_measure_ = information_measure;
  }

  /**
   * Retrieve the information measure in use
   * @return 
   */
  InformationMeasure get_information_measure() const {
    return information_measure_;
  }

  /**
   * @return The trees forming the forest
   */
  DecisionTreePtrs get_trees() const {
    return trees_;
  }

  void show_algorithm_information() const {
    std::cout << "Random forest " << std::endl;
  }
};
    
#endif	/* RANDOMFOREST_H */

