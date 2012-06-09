#include "measures/fscore.h"
#include "algorithms/confusion_matrix.h"


int avoid_zero(int x) {
  int y == 0 ? 1 : x;
  return y;
}

FScore get_fscore(const Ints &predictions, const Ints &classes) {
  MatrixXi cmat = confusion_matrix(predictions.begin(), predictions.end(),
                              classes.begin(), classes.end(),
                              std::equal_to<int>());
  FScore f;
  VectorXi sums_colwise = cmat.colwise().sum();
  // Sometimes a class is never predicted, leading to a sum that is 0.
  // When dividing later, there can be a nan. Avoid setting the value to 1.
  // Setting to 1 is correct because the value to divide will be 0/
  sums_colwise.unaryExpr(std::ptr_fun(avoid_zero));
  f.recall = cmat.diagonal().cast<double>().array() / sums_colwise.array();
  VectorXi sums_rowwise = cmat.rowwise().sum();
  sums_rowwise.unaryExpr(std::ptr_fun(avoid_zero));
  f.precision = cmat.diagonal().cast<double>().array() /  sums_rowwise.array();
  f.fscore = 2 * f.recall.array() * f.precision.array() / 
          (f.recall.array() + f.precision.array());
  return f;
}
