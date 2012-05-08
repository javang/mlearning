#!/usr/bin/python

import sys
import os
import time
import logging
import numpy as np
import scipy.optimize as opt

from javi_ml.functions import sigmoid

log = logging.getLogger("neural_network")



#################################

# Implementation of a Neural Network with multiple layers
#################################


def add_bias_nodes(X):
    """
        Add a column of ones at the beginning of a matrix to include
        the bias nodes in a neural netwrok
    """
    return np.hstack( [np.ones( (X.shape[0], 1) ), X])


def forward(thetas_vector, X, topology):
    """ does a forward pass of the algorithm fro a neural network
        thetas - 1D vector with all the weights of the network
        X - data (Without the bias nodes column. It will be added)
        topology - Topology of the network. Used to extract the proper weights
        for each of the layers of the netwrok
    """
    w = get_weights_matrix(thetas_vector, topology, 1)
    log.debug("Forward X %s, w %s",X.shape, w.shape)
    h = step_forward(X, w)
    for layer in range(2,len(topology)):
        w = get_weights_matrix(thetas_vector, topology, layer)
        log.debug("Forward h %s, w %s",h.shape, w.shape)
        h = step_forward(h, w)
    log.debug("Forward final h %s",h.shape)
    return h

def forward_get_all(thetas_vector, X, topology):
    """ 
        Same as forward, but it returns all the matrices generated 
        when doing a forward pass of the algorithm
    """
    Z = [np.copy(X)]
    for layer in range(1,len(topology)):
        w = get_weights_matrix(thetas_vector, topology, layer)
        V = step_forward(Z[-1], w)
        Z.append(V)
    return Z

def step_forward(X, w):
    """
        Does a forward step of the algorithm, by computing the values of
        the activation function
        X - data (no bias nodes)
        w - matrix of weights for the neurons in the layer
    """
    V = add_bias_nodes(X)
    r = sigmoid( V.dot(w.T) )
#    log.debug("Step forward returning: %s\n %s ", r.shape, r)
    return r


def get_layer_weights_dims(topology, layer):
    """ dimensions and size of the matrix of weights for layer l.
        l >=1 always. l0 are the inputs of the network
    """
    cols = topology[layer-1] + 1
    rows = topology[layer]
    size = rows * cols
#    log.debug("Theta dims for layer %s: %sx%s",l,rows, cols)
    return rows, cols, size


def get_weights_matrix(thetas_vector, topology, layer):
    """
        recover the matrix of weights theta corresponding to a layer
        layer >= 1. Layer 0 are the inputs
    """
    # starting position for the values of the weights of the layer
    begin = 0
    for i in range(1,layer):
        r, c, isize = get_layer_weights_dims(topology, i)
        begin += isize
    nrows, ncols, size = get_layer_weights_dims(topology, layer)
    end = begin + size
    w = thetas_vector[begin:end]
    # reorganize the vector into a matrix
    v = w.reshape(nrows, ncols)
#    log.debug(" *** theta layer %s (%s, %s)",layer, begin, end)
#    log.debug(" *** theta %s reorganized [%s] %s",w.shape, layer,v.shape)
    return v


def error(thetas_vector, X, y, topology):
    """ Error of the neural network
        thetas - a vector with all the parameters of the neural network,
                  one after another.
        In order to perform the forward calculation, the matrices of the
        weights of each of the layers are reconstructed first
        y - correct values
        thetas - a list of the matrices of weights for each of the layers
    """
    h = forward(thetas_vector, X, topology)
    m = X.shape[0] # Number of samples
    e = (-1./m) * np.sum(y * np.log(h) + (1 - y) * np.log(1-h))
    e = np.sum(e)
    log.debug("*** error: %s", e)
    return e


def error_simple(thetas_vector, X, y, topology):
    m = X.shape[0] # Number of samples
    w1 = get_weights_matrix(thetas_vector, topology, 1)
    z2 = step_forward(X, w1)
    a2 = add_bias_nodes(z2)
    w2 = get_weights_matrix(thetas_vector, topology, 2)
    h = step_forward(z2, w2)
    e = (-1./m) * np.sum(y * np.log(h) + (1 - y) * np.log(1-h))
    log.debug("*** error: %s", np.sum(e))
    return np.sum(e)

def gradient_simple(thetas_vector,X,y,topology):
    m = X.shape[0]
    a1 = add_bias_nodes(X)
    w1 = get_weights_matrix(thetas_vector, topology, 1)
    z2 = step_forward(X, w1)
    a2 = add_bias_nodes(z2)
    w2 = get_weights_matrix(thetas_vector, topology, 2)
    h = step_forward(z2, w2)
    delta = h - y
    grad2 = delta.T.dot(a2) / m
    delta = delta.dot(w2) * a2 * (1-a2)
    delta = delta[:,1:]
    grad1 = delta.T.dot(a1) / m
    log.debug("a1 %s w1 %s z2 %s a2 %s w2 %s h %s", a1.shape, w1.shape,
                                  z2.shape, a2.shape, w2.shape, h.shape)
    x = np.hstack([grad1.flatten(), grad2.flatten()])
    log.debug("Gradient %s\n%s",x.shape, x)
    return np.hstack([grad1.flatten(), grad2.flatten()])

def gradient(thetas_vector, X, y, topology):
    """
        compute the gradient of the weights for each of the layers, by using
        the back propagation algorithm
    """
#    log.debug("Computing gradient")
#    log.debug("==> Current thetas vector %s",thetas_vector)
    m = X.shape[0] # Number of samples
    # Z has all the outputs of the neurons (but no the bias nodes)
    Z = forward_get_all(thetas_vector, X, topology)
    # add the bias terms to all matrices in A (except the last one, the outputs)
    A = [add_bias_nodes(z) for z in Z[:-1]]
    for i, a in enumerate(A):
        log.debug("A[%s] %s",i,A[i].shape)
    # result (not stored in A)
    h = Z[-1]
    delta = h - y
    # index for the layer
    layer = len(topology) - 1
    log.debug("gradient => layer %s delta %s", layer, delta.shape)
    # index for the elements of A. A contains the matrices of
    # intermediate values of the neural network, but neither the
    # inputs not the outputs. It has 2 elements less than the number of layers
    gr = 1./m * delta.T.dot(A[layer-1])
    grad = gr.flatten()
    layer -= 1
    while( layer >= 1):
        w = get_weights_matrix(thetas_vector, topology, layer + 1)
        log.debug("gradient => layer %s delta %s w %s A[%s] %s",
                      layer, delta.shape, w.shape, layer, A[layer].shape)
        delta = delta.dot(w) * A[layer] * (1- A[layer])
        # remove first column of the new delta, which corresponds to the bias nodes
        delta = delta[:,1:]
        log.debug("gradient ===> layer %s delta/wo bias %s A[%s] %s",
                  layer, delta.shape, layer-1, A[layer-1].shape)
        gr = 1./m * delta.T.dot(A[layer-1])
        grad = np.hstack([gr.flatten(), grad])
        layer -= 1
#    log.debug("Returning grad %s %s", grad.shape, grad)
    return grad

def numerical_gradient(thetas_vector, X, y, topology):
    """
        compute the gradient of the weights for each of the layers, by using
        the back propagation algorithm
    """

    eps = 1e-5
    grad = np.zeros(thetas_vector.shape[0])
    for i in range(thetas_vector.shape[0]):
        x = np.copy(thetas_vector)
        x[i] = x[i] + eps
        fh = error_simple(x, X, y, topology)
        x[i] = x[i] - 2*eps
        f0 = error_simple(x, X, y, topology)
        grad[i] = (fh-f0)/(2*eps)

    return grad


class NeuralNetworkMultipleLayers:


    def __init__(self,):
        self.trained = False

    def set_topology(self, network_topology=[3,4,3]):
        """
            The network topology is the number of layers, and the number of
            neurons to put on each layer. The default (which is just an
           example is [3 inputs, 4 neurons in the hidden layer, 3 outputs]
           More layers can be added with more numbers. Eg [3,4,5,3] has 2
           hidden layers of 4 and 5 neurons respectively
        """
        log.info("Setting the network topology")
        # set the topology of the network and the matrices of weights
        self.nt = network_topology
        np.random.seed()
        sizes = [ get_layer_weights_dims(self.nt, i)[2]
                                    for i in range(1, len(self.nt))]

        for i in range(1, len(self.nt)):
            r,c, s = get_layer_weights_dims(self.nt, i)
            log.debug("Weights layer %s w %sx%s",i,r,c)
        # all weights of the network in a vector
        self.thetas_vector = (np.random.rand(sum(sizes)) - 0.5) * 0.00001
        log.info("Number of parameters of the network: %s",
                                            self.thetas_vector.shape)

                                        


    def train_with_early_stopping(self, data, y, dataval, yval, iters=30):
        """
            Trains the neural network using the training set. The learning
            stops when the error of the validation set, not used for training,
            starts to raise.
            training_set - matrix of features. Each row is a data point
            y - know values for the training set
            validation_set - Matrix of features for the points used as validation
            yval - know values for the training set
        """
        pass
        
        
        
        
    def train(self, data, y, iters=30):
        """ Data is a matrix of values  with the rows being the data points
            and the columns the variables/features.
            y is the matrix of expected results
            - iters: maximum number of iterations to perform
        """
        log.debug("Training the network with %s data points", data.shape[0])
        log.info("THETAS 0: %s",self.thetas_vector)
        if(self.regularize):
            log.info("Training the neural network " \
                  "with regularization. tau = %s", self.tau)
            ret = opt.fmin_bfgs(self.regularized_error, self.thetas_vector,
                    self.regularized_gradient,
                    args=(data, y, self.nt, self.tau),  maxiter=iters)
            
        else:
            log.info("Training the neural network without regularization")
    #        ret = opt.fmin_ncg(error, self.thetas_vector, numerical_gradient,
    #                args=(data, y, self.nt), epsilon=1e-7, maxiter=iters)
            ret = opt.fmin_bfgs(error, self.thetas_vector, gradient,
                    args=(data, y, self.nt),  maxiter=iters)
    #        ret = opt.fmin(error, self.thetas_vector,
    #                args=(data, y, self.nt),  maxiter=iters)
        log.info("FINAL ERROR %s",error(ret, data, y, self.nt))
        log.info("FINAL WEIGHTS FOR THE NETWORK \n%s", ret)
        # recover all weight as matrices
        self.trained_thetas = []
        begin = 0
        for i in range(1, len(self.nt)):
            rows, cols, size  = get_layer_weights_dims(self.nt, i)
            log.debug("Trained theta[%s], %sx%s size %s begin %s",
                        i, rows, cols, size, begin)
            end = begin + size
            w = ret[begin:end]
            log.debug("%s",w)
            v = w.reshape(rows, cols)
            self.trained_thetas.append(v)
            begin = end

        log.info("Finished training theta %s", self.trained_thetas)
        self.trained = True
                
    def train_with_learning_rate(self, data, y, rate, iters):
        m = data.shape[0]
        rows, cols, size = get_layer_weights_dims(self.nt, 2)
        w2 = (np.random.rand(rows, cols) - 5) * 0.04
        rows, cols, size = get_layer_weights_dims(self.nt, 1)
        w1 = (np.random.rand(rows, cols) - 5) * 0.04
        log.debug("w1 %s w2 %s",w1.shape, w2.shape)
        a1 = add_bias_nodes(data)
        for i in range(iters):
            z2 = sigmoid(a1.dot(w1.T))
            a2 = np.hstack([np.ones((z2.shape[0],1)), z2])
            h = sigmoid(a2.dot(w2.T))
            delta = (y-h) * h * (1-h)
            print "error" , sum(delta)
            #log.debug( "delta3 %s a2 %s",delta.shape, a2.shape)
            w2 += rate * delta.T.dot(a2)
            #print "w2\n",w2
            xdelta = delta.dot(w2) * a2 * (1-a2)
            xdelta = xdelta[:,1:]
            #log.debug( "delta2 %s data %s",delta.shape, data.shape)
            w1 += rate * delta.T.dot(a1)
            #print "w1\n",w1

        self.trained_thetas = [w1, w2]
        log.info("Finished training % iterations. Thetas\n%s", iters,   
        self.trained_thetas)
        self.trained = True



    def predict(self, input):
        if(not self.trained):
            raise ValueError("The network has to be trained before predicting")
        h = input
        for w in self.trained_thetas:
            h = step_forward(h, w)
        return h


    def save_trained_values(self, fn):
        """
            Saves the topology of the network and the trained weights to file
        """
        if(not self.trained):
            raise ValueError("The network has to be trained before saving")

    def load_trained_network(self, fn):
        """ Reads a file with the topology of the network
            and sets the all the parameters
        """
        # read
        self.trained = True

    def set_regularize(self, reg=False, tau=0):
        """
            Apply regularization using parameter tau
        """
        self.regularize = reg
        self.tau = tau
        
        
    def regularized_error(self, weights, data,y, topology, tau):
        """
            Add regularization to the error. 
            tau - the regularization term
        """
        m = data.shape[0]
        err = error(weights, data, y, topology)
        err += (tau/(2*m)) * np.sum(weights[1:]**2)
        return err
        
    def regularized_gradient(self, weights, data, y, topology, tau):
        """docstring for regularized_graident"""
        m = data.shape[0]
        grad = gradient(weights, data, y, topology)
        grad[1:] += tau /m * weights[1:]
        return grad
        
        
        
class Recorder(object):
    """ class to save a bunch of values"""
    def __init__(self):
        self.grad = []
        self.ngrad = []


if __name__ == "__main__":


    import ConfigParser
    cparser = ConfigParser.SafeConfigParser()

    import optparse
    parser = optparse.OptionParser(description="help_header")

    parser.add_option("--i",
                    dest="fn_input",
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

    logging.root.setLevel(logging.DEBUG)


    nn = NeuralNetworkMultipleLayers()
    nn.set_topology([2,2,2])
    inputs = np.array([[0,0],[0,1],[1,0],[1,1]])
    targets = np.array([[0,1],[1,0],[1,0],[0,1]])
    nn.train(inputs, targets, iters=100)
#    nn.train_with_learning_rate(inputs, targets,0.5,1000)
    y = nn.predict(inputs)
    print "x =", inputs
    print "prediction", y



    import marsland_ml.mlp.mlp as mlp
    x = mlp.mlp(inputs, targets,2)
    x.mlptrain(inputs, targets, eta=1, niterations=12000)
    a = add_bias_nodes(inputs)
    print x.mlpfwd(a)
    