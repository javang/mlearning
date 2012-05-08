function [outnodes] = depth_first(node, outnodes)
    if ~isempty(node.left)  
        outnodes = depth_first(node.left, outnodes);
    end
    if ~isempty(node.right)
        outnodes = depth_first(node.right, outnodes);
    end
    outnodes = [outnodes node];
end