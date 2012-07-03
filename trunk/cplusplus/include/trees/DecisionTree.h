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
#include "core/definitions.h"
#include "core/SupervisedAlgorithm.h"
#include "utility/eigen_helper.h"
#include <memory>

class DecisionTree: public Tree, public SupervisedClassifier {
private:
  /**
  * Builds the decision tree (recursively).
  * @param node Node that is the root of the current tree
  * @param data Data matrix with data points as rows and features in the columns
  * @param classes Class for each of the data points
  */
  void get_tree(DecisionNodePtr node,
                const MatrixXd &data, 
                const VectorXi &classes);

  
  VectorXi get_prediction(const MatrixXd &data) const;
  int get_prediction_datapoint(const VectorXd &data) const;
  int get_prediction(DecisionNode *node,  const VectorXd &data_point) const;
  void do_training(const MatrixXd &data, const VectorXi &classes,
              VariableTypes variable_types);   
protected:
        InformationMeasure information_measure_;
        Bools columns_to_use_;
        VariableTypes variable_types_;
        //DecisionNodePtr root_;
public:

  DecisionTree (): information_measure_(GINI) {};

   

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

  /**
   * 
   * @return A vector of booleans showing if the feature/columns of the data
   * are used to compute the information gain. It changes during building the
   * decision tree
   */
  unsigned int number_of_columns_in_use() const;
  

  /**
   * Obtains the information gain that could obtained for each column of the
   * matrix 
   * @param data Matrix with the data (one data point per row)
   * @param classes Vector with the class for each data point
   * @param rows_to_use The rows of the matrix data that are used to compute
   * the gains. If this vector is empty, use all
   * @return Returns the tuple of (gain, the column that has the best 
   * information gain, the threshold for splitting continuous variables).
   * The threshold is 0 if the variable contained in a column is categorical
   */
  std::tuple<double, unsigned int, double>
                get_best_gain(const MatrixXd &data, 
                              const VectorXi &classes);
  
  
  void show_algorithm_information() const {
    std::cout << "decision tree " << std::endl;
  }
};
  
typedef std::shared_ptr<DecisionTree> DecisionTreePtr;
typedef std::vector<DecisionTreePtr> DecisionTreePtrs;


#endif	/* DECISIONTREE_H */

  
