/* 
 * File:   fscore.h
 * Author: javi
 *
 * Created on June 8, 2012, 10:52 AM
 */

#ifndef FSCORE_H
#define	FSCORE_H

#include "utility/eigen_helper.h"
#include <cassert>

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
            
  void calculate(const VectorXi &classes, const VectorXi &predictions);
  VectorXd get_recall() const;
  VectorXd get_precision() const;
  VectorXd get_fscore() const;
};


/**
 * Return 1 if x 0, otherwise return x
 * @param x
 * @return 
 */
long int avoid_zero(int x);

#endif	/* FSCORE_H */

