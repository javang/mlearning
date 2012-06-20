/* 
 * File:   SupervisedAlgorithm.h
 * Author: javi
 *
 * Created on June 20, 2012, 10:12 AM
 */

#ifndef SUPERVISEDALGORITHM_H
#define	SUPERVISEDALGORITHM_H

#include "utility/eigen_helper.h"
#include "core/types.h"

class SupervisedClassificationAlgorithm {
private:
  virtual void do_training(const MatrixXd &data, 
                           const VectorXi &classes,
                           VariableTypes variable_types) = 0;
  
  /**
   * Subclasses must implement their prediction mechanism
   * @param data a set of data points
   * @return A vector with the classes for the data points
   */
  virtual VectorXi get_prediction(const MatrixXd &data) const = 0 ; 
  
  /**
   * Prediction for a single data point
   * @param datapoint
   * @return The class the datapoint belongs to
   */
  virtual int get_prediction(const VectorXd &datapoint) const = 0 ; 
  
  
  // disable copy construction and assignment
  SupervisedClassificationAlgorithm(const SupervisedClassificationAlgorithm &s);
  void operator=(const SupervisedClassificationAlgorithm &s);

public:
  
  SupervisedClassificationAlgorithm();
  /**
   * Train the algorithm
   * @param data Data used to train the algorithm
   * @param classes Classes of the points in the data
   * @param variable_types Types of the features in the data 
   */
  void train(const MatrixXd &data,
             const VectorXi &classes,
             VariableTypes variable_types) {
    do_training(data, classes, variable_types);
  }
  
  /**
   * Get predictions for a set of data points
   * @param data
   * @return the classes for the data points
   */
  VectorXi predict(const MatrixXd &data) const {
    return get_prediction(data);
  }
  /**
   * Get a prediction for a data point
   * @param datapoint
   * @return get the class the point belongs to
   */
  int predict(const VectorXd &datapoint) const {
    return get_prediction(datapoint);
  };
  
  virtual ~SupervisedClassificationAlgorithm() {};
 
};

class SupervisedRegressionAlgorithm  {
  
private:
  virtual void do_training(const MatrixXd &data, const VectorXd &values) = 0;
  virtual VectorXd get_prediction(const MatrixXd &data) const = 0 ; 
  virtual double get_prediction(const VectorXd &data) const = 0 ; 
  
  
  SupervisedRegressionAlgorithm(const SupervisedRegressionAlgorithm &s);        
  
  void operator =(const SupervisedRegressionAlgorithm &s);

public:
  
  SupervisedRegressionAlgorithm();

  void train(const MatrixXd &data, const VectorXd &values) {
    do_training(data, values);
  }
  
  
  
  /**
   * Get a prediction for a data point
   * @param datapoint
   * @return get the class the point belongs to
   */
  double predict(const VectorXd &datapoint) const {
    return get_prediction(datapoint);
  }
  
  /**
  * Get predictions for a set of data points
  * @param data
  * @return the classes for the data points
  */
  VectorXd predict(const MatrixXd &data) {
    return get_prediction(data);
  }
  
  virtual ~SupervisedRegressionAlgorithm() {};
  
};



#endif	/* SUPERVISEDALGORITHM_H */

