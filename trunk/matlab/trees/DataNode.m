classdef DataNode < TreeNode & handle
    properties
        data;
    end
    methods
        function node = DataNode(first_child,next_sibling, parent)
           super_args = {}; 
           if nargin ~= 0 
              super_args{1} = first_child;
              super_args{2} = next_sibling;
              super_args{3} = parent;
           end
            node = node@TreeNode(super_args{:});
        end
        
        function self = set.data(self, X)
            self.data = X;
        end
        
        function y = get.data(self)
            y = self.data;
        end
    end
end