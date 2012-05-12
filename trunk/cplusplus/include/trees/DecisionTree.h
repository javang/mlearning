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
#include "trees/information_gain.h"
#include "utility/definitions.h"

#include <Eigen/Dense>

class DecisionTree: public Tree {
private:
     unsigned int get_prediction(DecisionNode *node, 
                                 const VectorXd &data_point) const;
protected:
        InformationMeasure information_measure_;
        Bools columns_in_use_;
        VariableTypes variable_types_;
        DecisionNodePtr root_;
public:

  DecisionTree (): information_measure_(GINI) {};

  
  /**
   * Train the tree. 
   * @param data Matrix with as many rows as data points an as many colums as
   *        features
   * @param classes The classes of each of the data points
   * @param variable_types_ The type of features. Continuous or categorical
   */
  void train(const MatrixXd &data, const VectorXi &classes,
              VariableTypes variable_types);
  
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

  unsigned int number_of_columns_in_use() const;
  

  void get_tree(DecisionNodePtr node,
                const MatrixXd &data, 
                const VectorXi & classes,
                const Ints &rows_to_use=Ints());
  
  std::tuple<double, double, int> get_best_gain(const MatrixXd &data, 
                              const VectorXi &classes,
                              const Ints &indices_to_use);
};
  
typedef std::vector<DecisionTree> DecisionTrees;
typedef std::shared_ptr<DecisionTree> DecisionTreePtr;
typedef std::vector<DecisionTreePtr> DecisionTreePtrs;




#endif	/* DECISIONTREE_H */
