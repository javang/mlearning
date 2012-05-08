classdef DecisionNode < TreeNode
	properties
        column_for_next_split;
	    feature_value; 
        feature; 
        % 'lower' if the value must be lower than the threshold, or 'upper'
        threshold_type;         
        class; % the class for the variable that is predicted
    end
	
    methods
               
        function y = get.column_for_next_split(self)
            y = self.column_for_next_split;
        end
        function self = set.column_for_next_split(self, y)
            self.column_for_next_split = y;
        end
        
        function y = get.threshold_type(self)
            y = self.threshold_type;
        end
        function self = set.threshold_type(self, y)
            self.threshold_type = y;
        end
        
        function y = get.feature_value(self)
            y = self.feature_value;
        end
        
        function self = set.feature_value(self, y)
            self.feature_value = y;
        end

         function y = get.feature(self)
            y = self.feature;
        end
        function self = set.feature(self, y)
            self.feature = y;
        end
       
        function y = get.class(self)
            y = self.class;
        end
        function self = set.class(self, y)
            self.class = y;
        end
        
        function self = set_feature(self, feature, value)
            self.feature = feature;
            self.feature_value = value;
        end
               
        
        function x = matches_value(self, value, is_categorical)
            if(is_categorical)
                x = self.feature_value == value;
            elseif(self.threshold_type == InfoGainThreshold.lower)
                %fprintf('checking match for threshold lower\n')
                x = value <= self.feature_value;
            elseif(self.threshold_type == InfoGainThreshold.higher)
                %fprintf('checking match for threshold higher\n')
                x = value > self.feature_value;
            else
                exception = MException('DecisionNode:matches_value', ...
                   ['Incorrect matching_value function behavior. ' ...
                   'Check self.threshold value']);
                throw(exception)                
            end
                
        end

        
        function show(self)
            show@TreeNode(self);
            if ~isempty(self.feature)
                fprintf('Feature: %d ',self.feature);
            end
            if ~isempty(self.feature_value)
                fprintf('Value: %d ',self.feature_value);
            end
            if ~isempty(self.class)
                fprintf('Class: %s ', char(self.class));
            end
            if(~isempty(self.column_for_next_split))
                fprintf('Next split is feature %d\n',self.column_for_next_split)
            end
            fprintf('\n');
        end
    end
end
    
 