/* 
 * File:   confusion_matrix.h
 * Author: javi
 *
 * Created on June 8, 2012, 11:03 AM
 */

#ifndef CONFUSION_MATRIX_H
#define	CONFUSION_MATRIX_H

#include "utility/definitions.h"
#include "utility/print_utils.h"
#include "utility/eigen_helper.h"
#include <algorithm> 
#include <utility>
#include <cassert>
#include <map>

template <class FirstIterator,class SecondIterator>
MatrixXi get_confusion_matrix(FirstIterator predictions_first,
                          FirstIterator predictions_last,
                          SecondIterator classes_first,
                          SecondIterator classes_last) {
  unsigned int sizep = predictions_last - predictions_first;
  unsigned int sizec = classes_last - classes_first;
  assert(sizep == sizec);  
  IntsSet unique_classes(classes_first, classes_last);
  IntsSet unique_predictions(predictions_first, predictions_last);
  unsigned int size = unique_classes.size() > unique_predictions.size() ? 
                         unique_classes.size() : unique_predictions.size();
  MatrixXi cmat = MatrixXi::Zero(size, size);
  std::map< int, int> class_to_index;
  std::map< int, int> prediction_to_index;
  
  unsigned int index = 0;
  for (IntsSet::iterator it = unique_predictions.begin();
       it != unique_predictions.end(); ++it, ++index) {
    prediction_to_index.insert( IntPair(*it, index));
  }
  index = 0;
  for (IntsSet::iterator it = unique_classes.begin();
    it != unique_classes.end(); ++it, ++index) {      
    class_to_index.insert( IntPair(*it, index));
  }
  
  FirstIterator pr_it = predictions_first;
  SecondIterator cl_it = classes_first;
  for ( ; pr_it != predictions_last;  ++pr_it, ++cl_it) {
    IntPair j = *(class_to_index.find(*cl_it));
    IntPair i = *(prediction_to_index.find(*pr_it));
    cmat(i.second, j.second) += 1;
  }
  return cmat;
}


#endif	/* CONFUSION_MATRIX_H */

