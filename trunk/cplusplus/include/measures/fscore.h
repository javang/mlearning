/* 
 * File:   fscore.h
 * Author: javi
 *
 * Created on June 8, 2012, 10:52 AM
 */

#ifndef FSCORE_H
#define	FSCORE_H

#include "utility/eigen_helper.h"
#include "algorithms/confusion_matrix.h"

/**
 * FScore for a set of variables.
 * Recall is true_positives / (true_positives + false_negatives)
 * Precision is true_positives / (true_positives + true_negatives)
 * fscore = 2 * recall * precision / (recall + precision)
 */
struct FScore {
private:
  VectorXd fscore_;
  VectorXd precision_;
  VectorXd recall_;
public:
  FScore() {};
  
  /**
   * Calculate the fscore given the predictions and the true classes
   * @param classes
   * @param predictions
   * T can be a std::vector<int> or a VectorXi
   */
  template<class T>
  void calculate(const T &predictions, const T &classes) {
    MatrixXi cmat = get_confusion_matrix(predictions, classes);
    calculate_from_confusion_matrix(cmat);
  }

  /**
   * Calculates the fscore using the confusion matrix
   * @param cmat
   */
  void calculate_from_confusion_matrix(const MatrixXi &cmat);

  
  VectorXd get_recall() const;
  VectorXd get_precision() const ;
  VectorXd get_fscore() const;
};


/**
 * Return 1 if x 0, otherwise return x
 * @param x
 * @return 
 */
int avoid_zero(int x);
double avoid_zero_double(double x);

#endif	/* FSCORE_H */

