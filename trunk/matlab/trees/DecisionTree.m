classdef DecisionTree < Tree & handle
    properties
        gain_measure;
        % columns that are used for each step during building the tree
        columns_in_use;
        % vector indicating for each feature if it is categorical (true)
        % or not (false).
        are_categorical;
    end
    
    
    
    methods
        function self = DecisionTree()
            root = DecisionNode;
            self = self@Tree(root);
            self.gain_measure = InfoMeasure.gini; % it can be also 'entropy'
        end
        
        function self = set.gain_measure(self, m)
            self.gain_measure = m;
        end
            
        %{
           Train the tree.
            - data is expected to be a real matrix of datapoints (rows)
                and features (cols)
            - Y the expected class for each datapoint
            - are_categorical is a vector with 0 for a continuous 
              variable and 1 for a categorical one
        %} 
        function self = train(self, X, Y, are_categorical)
            self.columns_in_use = ones(1,size(X,2));
            self.are_categorical = are_categorical;
            root = DecisionNode;
            self.root = self.get_tree(root, X, Y);            
        end
        
        
        function tree = get_tree(self, node, X, Y)
            if (number_of_categories(Y) == 1 ||  ...
                                    self.number_of_columns_in_use() == 1)
                node.class = get_class(Y);
                tree = node;
            else
                [gain, column, threshold] = self.best_gain(X, Y);
                node.column_for_next_split = column;
                self.columns_in_use(column) = false;
                is_categorical = self.are_categorical(column);
                if is_categorical
                    values = unique(X(:, column));
                    n_values = size(values,1);
                    for i = 1:n_values
                        [Z, W] = get_matrices_for_value(X, Y,...
                                                        column, values(i));
                        child = DecisionNode;
                        child.set_feature(column, values(i));
                        child_tree = self.get_tree(child, Z, W);
                        
                        node.add_child(child_tree);
                    end
                else
                    h = [InfoGainThreshold.higher InfoGainThreshold.lower];
                    for i = 1:2
                        [Z, W] = get_matrices_for_threshold( ...
                                        X, Y, column, threshold, h(i));
                        child = DecisionNode;
                        child.set_feature(column, threshold);
                        child.threshold_type = h(i);
                        child_tree = self.get_tree(child, Z, W);
                        node.add_child(child_tree);
                    end
                end
                tree = node;         
            end
        end
        
               
        function [bestGain, best_feature, threshold] = best_gain(self, X, Y)
            cols = size(self.columns_in_use,2);
            bestGain = 0; % best gain
            threshold = 0;
            best_feature = 0;
            for i = 1:cols
                if(self.columns_in_use(i))
                    [g, thr] = info_gain(X(:, i), Y, ...
                            self.are_categorical(i), self.gain_measure);
                    if(g > bestGain)
                        bestGain = g; 
                        best_feature = i;
                        threshold = thr;
                    end
                end
            end
        end

        
        function n = number_of_columns_in_use(self)
            n = sum(self.columns_in_use);
        end

        
        
        function show(self)
            show@Tree(self);
        end
        
        
        function predictions = predict(self, data)
           %{
                Predict the class in Y for each of the datapoints in X
                Each row is a datapoint
            %}
           n = size(data,1);
           predictions = zeros(n, 1);
           for i = 1:n
               predictions(i, 1) = self.get_prediction(self.root, data(i, :));
           end
            
        end
            
        function prediction = get_prediction(self, node, x)
            %{
                returns the predicted class for this node.
                x is a row vector datapoint 
            %}
            if(node.isleaf())
                prediction = node.class;
                %sprintf('I have a prediction for x => %s\n',char(prediction))
                return 
            else
                col = node.column_for_next_split;
                value_xcol = x(col);
                children = node.get_children();
                n_children = node.get_number_of_children();
                for i = 1:n_children
                    if(children(i).matches_value(x(col), ...
                                        self.are_categorical(col)))
                        prediction = self.get_prediction(children(i), x);
                        return
                    end
                end
                exception = MException('DecisionTree:get_prediction', ...
                   'Value for the node not found in the tree');
                throw(exception)
            end
        end
    end
end
           
    
    function n_cats = number_of_categories(Y)
        n_cats = size(unique(Y),1);
    end
       
    % class is chosen as the value that appears more times
    function class = get_class(Y)
        counts = levelcounts(Y);
        levels = getlevels(Y);
        [max_val, index] = max(counts);
        class = levels(index);
    end
    
    
    % get the datapoints in matrices X and Y where the column "column"
    % in X has the value "value"
    function [Z, W] = get_matrices_for_value(X, Y, column, value)
        indices = (X(:, column) == value);
        Z = X(indices, :);
        W = Y(indices, :);
    end
        
    % Same as previous function but for values lower or higher
    function [Z, W] = get_matrices_for_threshold(X, Y, column, ...
                                            threshold, lower_or_higher)                                        
        if(lower_or_higher == InfoGainThreshold.lower)
            indices = (X(:, column) <= threshold);
        else
            indices = (X(:, column) > threshold);
        end
        Z = X(indices, :);
        W = Y(indices, :);
    end
        

 
