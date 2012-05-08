#!/usr/bin/python

import sys
import os
import time
import logging
from javi_ml.functions import sigmoid
import scipy.optimize as opt
import numpy as np
import hashlib

log = logging.getLogger("Logreg")


class SigmoidCache:
    """
        Store the values of the values of the sigmoid for some thetas to avoid computing
        them. Keep only some arrays of values in the cache to avoid memory problems
    """
    def __init__(self):
        self.cache = dict()
        self.cache_size = 4

    def __call__(self, theta , X):
        # create a hash key for theta
        b = theta.view(np.uint8) # byte view of theta
        key = hashlib.sha1(b).hexdigest()
        if(not self.cache.has_key(key)):
            log.debug("Size X %s",X.shape)
            log.debug("Size theta %s",theta.shape)
            z = np.dot(X, theta)
#            print "z",z
            h = sigmoid(z)
#            print "h",h
            if(len(self.cache) >= self.cache_size):
                self.cache.popitem()
            self.cache[key] = h
        log.debug("SigmoidCache Size h %s",self.cache[key].shape)
        return self.cache[key]     
            


def error(theta, X, y, sigmoid_cache):
    """
        Computes the error of the logistic regressor between the estimations h
        for the values of X and the true values y. Theta is a numpy vector
         withe parameters for the regression
    """
    log.debug("Error theta%s",theta)
    m = X.shape[0]

#    h = sigmoid_cache(theta, X)
    # A few naive tests give me that is better to compute the sigmoid directly
    # instead of using a cache. But I have to try with large datasets
    z = np.dot(X, theta)
    h = sigmoid(z)

    e = y * np.log(h) + (1 - y) * np.log(1-h)
    return (-1.)/m * np.sum(e)


def regularized_error(theta, X, y , sigmoid_cache, tau):
    """
        Compute the error and add the regularization term for the logistic
        regressor. Tau is the damping factor to use to the sum of squares
        of the weights theta.
    """
    m = X.shape[0]
    err = error(theta, X, y, sigmoid_cache)
    print "error no reg", err,
    # add the regularization term (the first weight in theta is not regularized)
    print "theta",theta[1:], "sum theta", tau/(2*m) * np.sum(theta[1:]**2),
    err += tau/(2*m) * np.sum(theta[1:]**2)
    print "error with reg", err
    return err

def gradient(theta, X, y, sigmoid_cache):
    """
       Computes the gradient of the error for the values of 
       X and the true values y. Theta is a numpy vector
         withe parameters for the regression
    """
    log.debug("Gradient theta %s",theta)
    m = X.shape[0]
    log.debug("Size X %s",X.shape)

#    h = sigmoid_cache(theta, X)
    z = np.dot(X, theta)
    h = sigmoid(z)

    log.debug("Size h %s",h.shape)
    a = (h-y)
    
    log.debug("Size a %s",a.shape)
    return 1./m * np.dot(np.transpose(X), a) 

def regularized_gradient(theta, X, y, sigmoid_cache, tau):
    """ Add the regularization term to the gradient """
    m = X.shape[0]
    grad = gradient(theta, X, y, sigmoid_cache)
    print "grad no reg",grad,
    grad[1:] += tau / m * theta[1:]
    print "grad with reg",grad
    return grad


class LogisticRegression:
    """
        Classifier that performs logistic regression
    """
    def __init__(self, regularize=False, tau=1):
        # Dictionary to store variables for caching
        self.cahe = dict()    
        self.regularize = regularize
        self.tau = tau

    def train(self, data, y, iters=400):
        """ Data is a matrix of values  with the rows being the data points
            and the columns the variables/features.
            y is the matrix of expected results
            - iters: maximum number of iterations to perform
        """
        m = data.shape[0]
        data = np.hstack([np.ones((data.shape[0],1)), data])
        theta0 = np.zeros(data.shape[1])
        sigmoid_cache = SigmoidCache()
        log.info("Training the logistic regressor. Regularized = %s", self.regularize)
        
        if(self.regularize):
            ret = opt.fmin_ncg(regularized_error, theta0, regularized_gradient, 
                    args=(data, y, sigmoid_cache, self.tau), maxiter=iters)
        else:
            # BFGS gives me a numerical problems with the dataset ../datasets/logreg/ex2data1.txt
    #        ret = opt.fmin_bfgs(error, theta0, gradient, 
    #                args=(data, y, sigmoid_cache), maxiter=iters)
    
            # this works
            ret = opt.fmin_ncg(error, theta0, gradient, 
                    args=(data, y, sigmoid_cache), maxiter=iters)
        # this works but does not use the gradient
#        ret = opt.fmin(error, theta0, args=(data, y, sigmoid_cache), maxiter=iters)

        self.trained_theta = ret
        log.info("Finished training theta %s", self.trained_theta)
    
    def predict(self, x):
        """
            Return the value of the classifier for the data point x
        """
        if(len(x.shape) == 1):
            p = np.hstack([np.ones(1), x])            
        else: 
            p = np.hstack([np.ones((x.shape[0],1)), x])
        z = np.dot(p, self.trained_theta)
        return sigmoid(z)
 
 


if __name__ == "__main__":
    
    
    import ConfigParser
    cparser = ConfigParser.SafeConfigParser()

    import optparse
    parser = optparse.OptionParser(description="help_header")

    parser.add_option("--o", 
                    dest="",
                    default = False,
                    help="")

    parser.add_option("--log",
                     dest="log", 
                     default=None,
                     help="File for logging ")


    args = parser.parse_args()

    # No positional argumenst in this script    
    args = args[0]
    if(len(sys.argv) == 1):
        parser.print_help()    
        sys.exit()

    if(args.log):
        logging.basicConfig(filename=args.log, filemode="w")
    else:
        logging.basicConfig(stream=sys.stdout)

    logging.root.setLevel(logging.INFO)

    

