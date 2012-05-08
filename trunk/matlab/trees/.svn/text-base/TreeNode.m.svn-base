classdef TreeNode < handle
% class to manage a node of a tree. The class is a handle because it
% has some arguments that need to be changed in a pointer-like way
    properties
        name;
        first_child;
        next_sibling;
        parent;
    end
    
    methods
        function node = TreeNode(parent, first_child, next_sibling)
            @handle;
            if nargin ~= 0
                node.first_child = first_child;
                node.next_sibling = next_sibling;
                node.parent = parent;
                node.name = 'No name';
            end
        end
        
        function self = set.first_child(self,node)
           self.first_child = node;
        end
        function node = get.first_child(self)
            node = self.first_child;
        end
    
        function self = set.next_sibling(self,node)
           self.next_sibling = node;
        end
        function node = get.next_sibling(self )
            node = self.next_sibling;
        end
        
        function self = set.parent(self, node)
           self.parent = node;
        end
        function node = get.parent(self)
            node = self.parent;
        end
        
        function self = set.name(self,node)
           self.name = node;
        end
        function name = get.name(self)
            name = self.name;
        end       
        
        function self = add_child(self, node)
            % the parent of the argument cannot be changed unles this class
            % is a handle
            x = self.first_child;
            if(isempty(x))
                self.first_child = node;
            else
                current = x;
                sibling = x.next_sibling;
                while ~isempty(sibling)
                    current = sibling;
                    sibling = current.next_sibling;
                end
                current.next_sibling = node; 
            end 
            node.parent = self;
        end

        
                
        function nodes = get_children(self)
            nodes = [];
            sibling = self.first_child;
            while(~isempty(sibling))
                nodes = [nodes sibling];
                sibling = sibling.next_sibling;
            end
        end
                
        function n = get_number_of_children(self)
            n = 0;
            sibling = self.first_child;
            while(~isempty(sibling))
                n = n + 1;
                sibling = sibling.next_sibling;
            end
        end
        
        function val = isleaf(self)
            val = isempty(self.first_child);          
        end
        
        function show(self)
            fprintf('Node: %s\n', self.name);
        end
                        
    end
end
