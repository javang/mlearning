
#include "measures/fscore.h"
#include "algorithms/confusion_matrix.h"


int avoid_zero(int x) {
  if(x == 0) return 1;
  return x;
}

void FScore::calculate(const VectorXi &predictions,
                       const VectorXi &classes) {
  MatrixXi cmat = get_confusion_matrix(predictions, classes);
  VectorXi sums_colwise = cmat.colwise().sum();
  // Sometimes a class is never predicted, leading to a sum that is 0.
  // When dividing later, there can be a nan. Avoid setting the value to 1.
  // Setting to 1 is correct because the value to divide will be 0.
  sums_colwise.unaryExpr(std::ptr_fun(avoid_zero));
  recall_ = cmat.cast<double>().diagonal().array() / sums_colwise.cast<double>().array();
  VectorXi sums_rowwise = cmat.rowwise().sum();
  sums_rowwise.unaryExpr(std::ptr_fun(avoid_zero));
  precision_ = cmat.cast<double>().diagonal().array() /  sums_rowwise.cast<double>().array();
  fscore_ = 2 * recall_.array() * precision_.array() / 
          (recall_.array() + precision_.array());
}

VectorXd FScore::get_recall() const {
  return recall_;
}

VectorXd FScore::get_precision() const {
  return precision_;
}

VectorXd FScore::get_fscore() const {
  return fscore_;
}
