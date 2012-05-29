classdef BinaryDataNode < BinaryTreeNode
    properties
        data;
    end
    methods
        function node = BinaryDataNode(left,right, parent)
           super_args = {}; 
           if nargin ~= 0 
              super_args{1} = left;
              super_args{2} = right;
              super_args{3} = parent;
           end
           node = node@BinaryTreeNode(super_args{:});
           data = [];
        end
        
        
        function self = set.data(self, X)
            self.data = X;
        end
        
        function y = get.data(self)
            y = self.data;
        end
    end
end