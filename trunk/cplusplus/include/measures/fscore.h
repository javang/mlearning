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
  VectorXd fscore;
  VectorXd precision;
  VectorXd recall;
};


FScore get_fscore(const Ints &classes, const Ints &predictions);

/**
 * Return 1 if x 0, otherwise return x
 * @param x
 * @return 
 */
int avoid_zero(int x);

#endif	/* FSCORE_H */

