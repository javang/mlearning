/* 
 * File:   confusion_matrix.h
 * Author: javi
 *
 * Created on June 8, 2012, 11:03 AM
 */

#ifndef CONFUSION_MATRIX_H
#define	CONFUSION_MATRIX_H

#include "utility/definitions.h"
#include <algorithm> 
#include <utility>
#include <cassert>

template <FirstIterator, SecondIterator, Predicate>
MatrixXi confusion_matrix(FirstIterator predictions_first,
                          FirstIterator predictions_last,
                          SecondIterator classes_first,
                          SecondIterator classes_last, 
                          Predicate pred) {
  unsigned int sizep = predictions_last - predictions_first;
  unsigned int sizec = classes_last - classes_first;
  assert(sizep, sizec);
  
  unsigned int size = sizep > sizec ? sizep: sizec;
  
  IntsSet unique_classes(classes_first, classes_last);
  IntsSet unique_predictions(predictions_first, predictions_last);
  unsigned int size = unique_classes.size() > unique_predictions.size() ? 
                         unique_classes : unique_predictions;       
  MatrixXi cmat = MatrixXi::Zero(size, size);
  std::map<unsigned int, unsigned int> class_to_index;
  std::map<unsigned int, unsigned int> prediction_to_index;
  
  for (FirstIterator it = prediction_to_index.begin(), unsigned int index = 0;
       it != prediction_to_index.end(), ++it, ++index) {
    prediction_to_index.insert( IntPair(*it, index));
  }
  for (SecondIterator it = unique_classes.begin(), unsigned int index = 0;
       it != unique_classes.end(), ++it, ++index) {
    class_to_index.insert( IntPair(*it, index));
  }
  for (cl_it=classes_first, pr_it=predictions_first;
          predictions_first != predictions_last; 
          ++predictions_first, ++classes_first) {
    unsigned int j = *(class_to_index.find(*cl_it));
    unsigned int i = *(prediction_to_index.find(*pr_it));
    cmat(i, j) += 1;
  }
  return cmat;
}


#endif	/* CONFUSION_MATRIX_H */

