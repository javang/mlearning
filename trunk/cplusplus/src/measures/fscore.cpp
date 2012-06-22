
#include "measures/fscore.h"
#include "algorithms/confusion_matrix.h"
#include <limits>

int avoid_zero(int x) {
  if(x == 0) return 1;
  return x;
}

double avoid_zero_double(double x) {
  if(fabs(x) <= std::numeric_limits<double>::epsilon()) return 1;
  return x;
}

void FScore::calculate_from_confusion_matrix(const MatrixXi &cmat) {
  // Sometimes a class is never predicted, leading to a sum that is 0.
  // When dividing later, there can be a nan. Avoid setting the value to 1.
  // Setting to 1 is correct because the value to divide will be 0.
  VectorXi sums = cmat.colwise().sum().unaryExpr(std::ptr_fun(avoid_zero));
  recall_ = cmat.cast<double>().diagonal().array() / sums.cast<double>().array();
  sums = cmat.rowwise().sum().unaryExpr(std::ptr_fun(avoid_zero));
  precision_ = cmat.cast<double>().diagonal().array() / sums.cast<double>().array();
  
  // Apply the same fix to the sum of the recall and precision arrays.
  VectorXd s = (recall_ + precision_).unaryExpr(std::ptr_fun(avoid_zero_double));
  fscore_ = 2 * recall_.array() * precision_.array() / s.array();
}

VectorXd FScore::get_recall() const {
  return recall_;
  // changed from the branch fix_readmatrix on the mac
}

VectorXd FScore::get_precision() const {
  return precision_;
}

VectorXd FScore::get_fscore() const {
  return fscore_;
}
