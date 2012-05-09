/* 
 * File:   DecisionTree.h
 * Author: javi
 *
 * Created on May 7, 2012, 7:35 PM
 */

#ifndef DECISIONTREE_H
#define	DECISIONTREE_H

#include "trees/Tree.h"
#include "trees/DecisionNode.h"

class DecisionTree: public Tree {
protected:
        InformationMeasure information_measure_;
        Bools columns_in_use_;
        Bools is_categorical_;
        DecisionNodePtr root_;
public:

  /**
   * Train the tree. 
   * @param data Matrix with as many rows as data points an as many colums as
   *        features
   * @param classes The classes of each of the data points
   * @param is_categorical The type of features. Continuous or categorical
   */
  void train(const MatrixXd &data, const VectorXi &classes,
              Bools is_categorical);
  
  VectorXi predict(const MatrixXd &data) const;

  
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

  unsigned int DecisionTree::number_of_columns_in_use() const;
  
  
};
  
typedef std::vector<DecisionTree> DecisionTrees;




#endif	/* DECISIONTREE_H */
