classdef Tree < handle
    properties
        root;
    end
    
    methods
        % start the tree with the root node
        function self = Tree(root)
            @handle;
            self.root = root;
        end
            
        function breath_first(x)
        end

        function depth_first(x)
        end

        function self = set.root(self,node)
            self.root = node;
        end
            
        function self = save(fn)
            % save the tree to a datafile
        end
        
        function self = load(fn)
            % load the tree from a datafile
        end
        
        function show(self)
            print_tree(self.root);
        end
        
    end
end



    % print the tree in preorder
    function print_tree(node)
        node.show()
        ch = node.get_children();
        n = size(ch,2);
        for i = 1:n
            fprintf('print tree for child %d\n',i)
            print_tree(ch(i));
        end
    end
   