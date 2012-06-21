/* 
 * File:   confusion_matrix.h
 * Author: javi
 *
 * Created on June 8, 2012, 11:03 AM
 */

#ifndef CONFUSION_MATRIX_H
#define	CONFUSION_MATRIX_H

#include "core/definitions.h"
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

/**
 * Get the confusion matrix comparing the classes predicted by an algorithm
 * and the true values
 * @param predictions Classes predicted by the algorithm. They must be stored
 * in a container that supports random access with the [] operator and has
 * the function size() returning the size of the container
 * @param classes True values for the classes. The container has the same 
 * requirements as before
 * @return The confusion matrix
 */
template<class T>
MatrixXi get_confusion_matrix(const T &predictions,
                              const T &classes) {
  assert(predictions.size() == classes.size());  
  IntsSet unique_classes, unique_predictions;
  for (std::size_t i = 0; i < classes.size(); ++i) {
    unique_classes.insert(classes[i]);
  }
  for (std::size_t i = 0; i < predictions.size(); ++i) {
    unique_predictions.insert(classes[i]);
  }
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
  for (unsigned int i = 0; i < predictions.size(); ++i) {
    IntPair pj = *(class_to_index.find(classes[i]));
    IntPair pi = *(prediction_to_index.find(predictions[i]));
    cmat(pi.second, pj.second) += 1;
  }
  return cmat;
}long




#endif	/* CONFUSION_MATRIX_H */

