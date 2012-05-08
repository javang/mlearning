import logging
import numpy as np

log = logging.getLogger("performance")

class PerformanceMeasures(object):
    """docstring for PerformanceMeasures"""
    def __init__(self,  p, y, ncats):
        self.m = None # confusion matrix
        self.create_confusion_matrix(p, y, ncats)
        
    def get_confusion_matrix(self):
        """        
         Compares the predictions in p with the actual values in y.
         The number of categories is used for the dimensions of the matrix:
         ncats x ncats
         The categories in p and y are used also for the indices of the matrix.
         Therefore, if there are 3 categories, the possible values in p and y
         are 0,1, and 2.
         
        """

        return self.m
    
    def create_confusion_matrix(self, p, y, ncats):
        """ confusion matrix 
            i - rows - Class predicted
            j - cols - Correct class
        """
        self.m = np.zeros((ncats,ncats))
        for i, j in zip(p,y):
            self.m[i,j] += 1
        
        
    def get_precision(self):
        """
         pr = TP / (TP + FP) = TP / number_of_predictions for a class
        """
        true_pos = np.diag(self.m)
        n_predicted = np.sum(self.m, 1) # (TP + FP)
        # if there is a category with no values prediced (null for example),
        # avoid the problem of dividing by 0.
        epsilon = 1e-5
        ind = np.where(n_predicted < epsilon)
        n_predicted[ind] = epsilon 
        log.debug("n_predicted %s", n_predicted)
        pr = true_pos / n_predicted 
        return pr
        
    def get_recall(self):
        """
         RECALL = TP / (TP + FN) = TP / n_elements_category
        """
        true_pos = np.diag(self.m)
        n_elements = np.sum(self.m, 0)
        epsilon = 1e-5
        ind = np.where(n_elements < epsilon)
        n_elements[ind] = epsilon 
        log.debug("n_elements %s", n_elements)
        re = true_pos / n_elements
        return re

    def get_f_score(self):
        prec = self.get_precision()
        rec = self.get_recall()
        f = 2*prec*rec / (prec + rec)
        print f
        return f