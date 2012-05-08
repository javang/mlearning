import sys
import os
import time
import logging
import csv
import numpy as np
import cPickle
import collections

log = logging.getLogger("nominal_vars")

NULL_CATEGORY = 0

class CategoricalFeature(object):

    def __init__(self, name):
        """
            Each categorical feature has a dictionary of categories and 
            of counts. The keys of the dictionaries are the names for the 
            categories. The values for "categories" are the indices of each
            category. The values for "counts" are the number of times
            that each category appears in the dataset
        """
        self.categories = collections.OrderedDict()
        self.counts= collections.OrderedDict()
        self.categories["NULL"] = NULL_CATEGORY
        self.counts["NULL"] = 0
        self.name = name

    def add_category(self, name):
        self.categories[name] = len(self.categories)
        self.counts[name] = 0
       
        
    def get_category_name(self, val):
        """ Given a value, return the category that it
            belongs to
        """
        for x,y in self.categories.iteritems():
            if val == y:
                return x
                
    def print_info(self):
        """ print the data for a given feature"""
        print "============",self.name,  "============"
        print "Categories", self.categories
        print "Counts", self.counts
        print "========================"


  
class CategoricalFeatures(collections.OrderedDict):
    """docstring for CategoricalFeatures"""
    
    def set_data_matrix_size(self, n_data, n_features):
        self.data_matrix = np.zeros((n_data, n_features), dtype=int)

        
    def add_text_feature(self, values, name,other_lim=False):
        """ 
            Reads a set of text values, and extracts all possible values as
            categories. Counts the numbers of values.

            - If other_lim is given, store all the categories with a count
                lower than the value of other_lim in a keyword OTHER
        """
        t0 = time.time()
        cf = CategoricalFeature(name)
        self[name] = cf                
        col = self.keys().index(name)
        for i, d in enumerate(values):   
            if self.is_null(d):
                cf.counts["NULL"] += 1
                continue
            if d not in cf.categories:
                cf.add_category(d)
            self.data_matrix[i, col] = int(cf.categories[d])
            cf.counts[d] += 1      
             
        if(other_lim != False):
            newcf = CategoricalFeature(name)
            newcf.add_category("OTHER")
            # numbers to give the new categories in cf.vals. The numbers change
            # because the categories that are going to be OTHER have now a 
            # different number
            new_indices = dict() 
            for c in cf.categories:
                count = cf.counts[c]
                if(count < other_lim):
                    newcf.counts["OTHER"] += count
                    # log.debug("Previous category %s is now %s", 
                    #                 cf.categories[c], newcf.categories["OTHER"])
                    new_indices[cf.categories[c]] = newcf.categories["OTHER"]
                else:
                    if(c not in newcf.categories):
                        newcf.add_category(c)
                        newcf.counts[c] += count
                    # log.debug("Previous category %s is now %s", 
                    #                 cf.categories[c], newcf.categories[c])
                    new_indices[cf.categories[c]] = newcf.categories[c]
            # Change the indices in the values
            for i in np.arange(self.data_matrix.shape[0]):
                self.data_matrix[i, col] = new_indices[ self.data_matrix[i,col] ]
            self[name] = newcf
        tf = time.time()        
        log.debug("Time to process feature %s: %s.", name, tf-t0)
        
        
    def add_feature_with_examples(self, values, name, examples):
        """
            Summarize a column of text values based on examples. If the word in the
            values contains any of the examples, it is put in that category.
            Otherwise it is stored in "other"
        """
        t0 = time.time()
        cf = CategoricalFeature(name)
        self[name] = cf
        for e in examples:
            cf.add_category(e)
        cf.add_category("OTHER")
        col = self.keys().index(name)
        
        for i, d in enumerate(values):    
            if self.is_null(d):
                cf.counts["NULL"] += 1
                self.data_matrix[i, col] = cf.categories["NULL"]
                continue
            examples_in_d = [e for e in examples if (e in d)]
            if(len(examples_in_d) == 0):
                cf.counts["OTHER"] += 1
                self.data_matrix[i, col] = cf.categories["OTHER"]
                
            else:
                if(len(examples_in_d) > 1):
                    # IF more than one example matches, get the longest match
                    lmax = 0
                    ex = ""
                    for e in examples_in_d:     
                        l = len(e)
                        if(l> lmax):
                            ex = e
                            lmax = l
                    cf.counts[ex] += 1
                    self.data_matrix[i, col] = cf.categories[ex]
                    
                else:
                    cf.counts[ examples_in_d[0] ] += 1
                    self.data_matrix[i, col] = cf.categories[examples_in_d[0]]
                    
        tf = time.time()        
        log.debug("Time to process feature %s: %s.", name, tf-t0)


    def add_continuous_feature(self, values, name, ncats):
        """ Read a data set with real numbers and splits it in ncats categories"""
        t0 = time.time()        
        cf = CategoricalFeature(name)
        self[name] = cf

        col = self.keys().index(name)
        numbers = []    
        for i, d in enumerate(values):   
            try:
                numbers.append(float(d))
            except:
                continue    
        numbers = np.array(numbers)        
        ma = numbers.max()
        mi = numbers.min()
        log.debug("min = %s, max = %s",mi, ma)
        counts, bins = np.histogram(numbers, ncats)
        # count categories. See process_number_categories for comments
        categories = bins[:-1] 
        for i, c in enumerate(categories):
            cf.categories[str(c)] = i + 1 # 0 index is for NULL 
            cf.counts[str(c)] = counts[i]
#        log.debug("Categories %s", categories)
#        log.debug("Counts %s", counts)
        for i,d in enumerate(values):
            try:
                dg = np.digitize([d], categories)
                self.data_matrix[i,col] = dg[0]
            except:
                self.data_matrix[i,col] = cf.categories["NULL"]
                cf.counts["NULL"] += 1
        tf = time.time()                
        log.debug("Time to process feature %s: %s.", name, tf-t0)
                                            

    def is_null(self,d):
        return d == "" or d == "NULL" or d == "null"
         
    def write_features_dict(self,fn):
        """ Save the all the categorical features dictionaries s"""
        log.info("Writting the features info to %s", fn)
        f = open(fn, "wb")
        cfs = [self[name] for name in self]
        cPickle.dump(cfs, f)
        f.close()

    def read_features_dict(self,fn):
        """ Reads the dictionary of features """
        log.info("Reading dictionary of features from %s", fn)
        f = open(fn, "rb")
        cfs = cPickle.load(f)
        for cf in cfs:
            self[cf.name] = cf 
        f.close()
            
    def get_data_matrix(self, fields = None):
        """ Return the matrix of numeric values for the fields
            - Fields is a list of keys present in the dictionary
        """
        if(fields != None):
            ks = self.keys()
            indices = [ ks.index(f) for f in fields]
            return self.data_matrix[:,indices]    
        else:
            return self.data_matrix
