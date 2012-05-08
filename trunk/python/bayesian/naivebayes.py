#!/usr/bin/python

import sys
import os
import time
import logging
import numpy as np

log = logging.getLogger("naivebayes")

#################################

# Naive Bayes Classifier

#################################

class NaiveBayes(object):
    """ Naive Bayers classifier """
    def __init__(self):
        self.features_matrices = []
        self.output_probs = None

    def build_probability_matrix(self, f, ncf, y, ncy, mu=1):
        """ Builds the matrix of pairs of values 
            (category feature, category output)
           - f - Values (categories) the feature f
           - y - Values (categories) for output y
           - ncf - number of categories in data f
           - ncy - number of categories in data y
            The values in f and y must contain the number of the
            categories: 0, 1, 2, ...
            These numbers are used for the indices of the matrix
            - mu - Laplace estimator variable
        """
        mat = np.zeros((ncf, ncy), dtype=float)
        
        for i,j in zip(f, y):
            mat[i,j] += 1.0
        # Laplace estimator: add mu (usually 1) to each count to avoid counts that are 0,
        # which would produce values of probabilites zero. 
        mat = mat + mu
        mat = mat / np.sum(mat, axis=0)
        # log.info("Building probability matrix: Rows (input categories)=%s," \
        #     " Cols (ouput categories) = %s",ncf,ncy)
        # save the logs of the probabilities. Otherwise
        # multiplying many small probabilities can give numerical problems
        self.features_matrices.append(np.log(mat))   
        
    def build_output_probabilities(self, y, nc, mu=1):
        """
            probabilities for each of the categories in the output if nothing
            else is given
        """
        m = np.zeros(nc)
        for i in y:
            m[i] += 1.0
        m = m + mu
        m = m / np.sum(m, axis=0)
        self.output_probs = np.log(m)
        
        
    def predict(self, data, null_category=0):
        """
            Data is a matrix of inputs, with one example per row
        """
        n = data.shape[0]
        log.info("Predicting category for the dataset. Entries %s", n)
        preds = np.zeros(n)
        for i in np.arange(n):
            preds[i] = self.predict_record(data[i,:], null_category)
        return preds    
            
    def predict_record(self, cats, null_category=0):
        """
            cats - vector with the category for each of the features
            null_category - If a value in "cats" has this value, is considered
            as null data, and is not taken into account for computing the 
            probabilities
        """

        """ Debug code, where I use the products of likelihoods instead of
         the logs. 
          the number of columns for each matrix is the same. Pick from first
        probs = np.ones(self.output_probs.shape[0])
        
        for i, cat in enumerate(cats):
            if(cat != null_category):
                vc = self.features_matrices[i][cat,:]
                probs *= vc
        probs *= self.output_probs
        probs = probs / sum(probs)
        return probs 
        """
        # the number of columns for each matrix is the same. The column number
        # are the categories. Pick this number from the first matrix
        loglikelihood = np.zeros(self.output_probs.shape[0])
        
        for i, cat in enumerate(cats):
            if(cat != null_category):
                vc = self.features_matrices[i][cat,:]
                loglikelihood += vc
        loglikelihood += self.output_probs
        likelihood = np.exp(loglikelihood)
        # normalize
        likelihood = likelihood / sum(likelihood)
        n = np.argmax(likelihood)
        # return the category with the maximum likelihood
        return n 

    def save_model(self, fn):
        if(not (len(self.features_matrices)>=1 and self.output_probs != None) ):
            raise ValueError("Cannot save. The classifier has not been trained")
        log.info("Saving Naive Bayes model to %s", fn)
        dicttosave = dict()
        for i,m in enumerate(self.features_matrices):
            dicttosave[str(i)] = m        
        dicttosave[str(i+1)] = self.output_probs
        np.savez(fn, **dicttosave)
        log.debug("saved log(output_probs) %s",self.output_probs.shape)
        
    
    def read_model(self, fn):
        log.info("Reading model from %s", fn)    
        v = np.load(fn)
        log.debug("read %s",v.files)
        fns = v.files
        n = len(fns) # number of matrices stored 
        self.features_matrices = []
        # matrices are stored with the number as key. Recover with the number
        for i in range(n-1):
            self.features_matrices.append(v[str(i)])
        self.output_probs = v[str(n-1)]
        log.debug("log(output_probs) %s, shape %s", self.output_probs,
                                                self.output_probs.shape )



