classdef RandomForest < handle
    properties
        % trees in the forest
        trees;
        % nmber of trees in the forest
        n_trees;
        % measure of the information gain (gini, entropy)
        gain_measure;
    end
    
    methods
        
        function self = RandomForest(n_trees)
            self.n_trees = n_trees; % number of trees in the forest 
            self.gain_measure = InfoMeasure.gini;
            self.trees = [];
            
        end

        function self = set.gain_measure(self, m)
            self.gain_measure = m;
        end

        
        function self = train(self, data, classes, are_categorical)
            %{
                train a number self.n_trees of decision trees.
                Each tree is trained choosing a random number of datapoints
            
                data - set of features used for training. Each row is a 
                    data point
                classes - the class for each datapoint
                are_categorical - a vector with true if the feature is
                    categorical and false otherwise. Eg [true false true]
                    means that a datapoint has 2 categorical variables, the
                    fist and the third
            %}
            n_points = size(data,1);
            for i=1:self.n_trees
                % Choose random set of data points
                n_choices = ceil(rand(1) * n_points);
                choices = randsample(n_points);
            
                T = DecisionTree;
                T.gain_measure = self.gain_measure;
                T.train(data(choices,:), classes(choices,:), are_categorical);               
                self.trees = [self.trees T];
            end
        end
        
        function classes = predict(self, data)
            % predicts the class of the datapoints in data
            predictions = zeros(size(data,1), self.n_trees);
            for i=1:self.n_trees
                predictions(:,i) = self.trees(i).predict(data);
            end
            % predit based on the most frequent value
            classes = mode(predictions,2);
        end
    end 
    
    
end

