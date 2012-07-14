/* 
 * File:   SupervisedAlgorithm.h
 * Author: javi
 *
 * Created on June 20, 2012, 10:12 AM
 */

#ifndef SUPERVISEDALGORITHM_H
#define	SUPERVISEDALGORITHM_H

#include "utility/eigen_helper.h"
#include "core/MLAlgorithm.h"
#include "types.h"

namespace ml {
namespace core {

class SupervisedClassifier: public MLAlgorithm {
private:
  virtual void do_training(const Eigen::MatrixXd &data, 
                           const Eigen::VectorXi &classes,
                           VariableTypes variable_types) = 0;
  
  /**
   * Subclasses must implement their prediction mechanism
   * @param data a set of data points
   * @return A vector with the classes for the data points
   */
  virtual Eigen::VectorXi get_prediction(const Eigen::MatrixXd &data) const = 0 ; 
  
  /**
   * Prediction for a single data point
   * @param datapoint
   * @return The class the datapoint belongs to
   */
  virtual int get_prediction_datapoint(const Eigen::VectorXd &datapoint) const = 0 ; 
  
  
  // disable copy construction and assignment
  SupervisedClassifier(const SupervisedClassifier &s);
  void operator=(const SupervisedClassifier &s);

public:
  
  SupervisedClassifier() {};
  /**
   * Train the algorithm
   * @param data Data used to train the algorithm
   * @param classes Classes of the points in the data
   * @param variable_types Types of the features in the data 
   */
  void train(const Eigen::MatrixXd &data,
             const Eigen::VectorXi &classes,
             ml::VariableTypes variable_types) {
    do_training(data, classes, variable_types);
  };
  
  /**
   * Get predictions for a set of data points
   * @param data
   * @return the classes for the data points
   */
  Eigen::VectorXi predict(const Eigen::MatrixXd &data) const {
    return get_prediction(data);
  };
  
  /**
   * Get a prediction for a data point
   * @param datapoint
   * @return get the class the point belongs to
   */
  int predict_datapoint(const Eigen::VectorXd &datapoint) const {
    return get_prediction_datapoint(datapoint);
  };
  
  virtual ~SupervisedClassifier() {};
  
 
};

class SupervisedRegression: public MLAlgorithm  {
  
private:
  virtual void do_training(const Eigen::MatrixXd &data, const Eigen::VectorXd &values) = 0;
  virtual Eigen::VectorXd get_prediction(const Eigen::MatrixXd &data) const = 0 ; 
  virtual double get_prediction(const Eigen::VectorXd &data) const = 0 ; 
  
  
  SupervisedRegression(const SupervisedRegression &s);        
  
  void operator =(const SupervisedRegression &s);

public:
  
  SupervisedRegression();

  void train(const Eigen::MatrixXd &data, const Eigen::VectorXd &values);
    
  /**
   * Get a prediction for a data point
   * @param datapoint
   * @return get the class the point belongs to
   */
  double predict(const Eigen::VectorXd &datapoint) const;
  
  /**
  * Get predictions for a set of data points
  * @param data
  * @return the classes for the data points
  */
  Eigen::VectorXd predict(const Eigen::MatrixXd &data);
  
  
  virtual ~SupervisedRegression() {};
  

  
};

typedef std::shared_ptr<SupervisedClassifier> SupervisedClassifierPtr;

} // core
} // ml

#endif	/* SUPERVISEDALGORITHM_H */

