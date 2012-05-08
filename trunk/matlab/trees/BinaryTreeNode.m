classdef BinaryTreeNode < handle
% class to manage a node of a tree. The class is a handle because it
% has some arguments that need to be changed in a pointer-like way
    properties
        left;
        right;
        parent;
    end
    
    methods
        function node = BinaryTreeNode(left, right, parent)
            @handle;
            if nargin ~= 0
                node.left = left;
                node.right = right;
                node.parent = parent;
            end
        end
        
        function self = set.left(self,node)
            self.left = node;
            node.parent = self;
        end
        function node = get.left(self)
            node = self.left;
        end
    
        function self = set.right(self,node)
            self.right = node;
            node.parent = self;
        end
        function node = get.right(self )
            node = self.right;
        end
        
        function self = set.parent(self,node)
            self.parent = node;
        end
        function node = get.parent(self )
            node = self.parent;
        end
    end
end
