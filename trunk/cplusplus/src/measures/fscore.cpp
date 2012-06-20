
#include "measures/fscore.h"
#include "algorithms/confusion_matrix.h"
#include "measures/fscore.h"


int avoid_zero(int x) {
  if(x ==0) return 1;
  return x;
}

FScore get_fscore(const Ints &predictions, const Ints &classes) {
  MatrixXi cmat = get_confusion_matrix(predictions.begin(), predictions.end(),
                              classes.begin(), classes.end());
  FScore f;
  VectorXi sums_colwise = cmat.colwise().sum();
  // Sometimes a class is never predicted, leading to a sum that is 0.
  // When dividing later, there can be a nan. Avoid setting the value to 1.
  // Setting to 1 is correct because the value to divide will be 0/
  sums_colwise.unaryExpr(std::ptr_fun(avoid_zero));
  f.recall = cmat.cast<double>().diagonal().array() / sums_colwise.cast<double>().array();
  VectorXi sums_rowwise = cmat.rowwise().sum();
  sums_rowwise.unaryExpr(std::ptr_fun(avoid_zero));
  f.precision = cmat.cast<double>().diagonal().array() /  sums_rowwise.cast<double>().array();
  f.fscore = 2 * f.recall.array() * f.precision.array() / 
          (f.recall.array() + f.precision.array());
  return f;
}
