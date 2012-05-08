
#ifndef TREE_H
#define TREE_H

#include "trees/TreeNode.h"

class Tree {

protected:
  TreeNodePtr root_;

public:
  Tree() {
    root_ = TreeNodePtr();
  }

  Tree(TreeNodePtr root) {
    root_ = root;
  }

  void print_tree() const {
    print_subtree(root_);
  }

  /**
   * Prints the subtree under the node root
   * @param root 
   */
  void print_subtree(TreeNodePtr root) const;

};

typedef std::vector<Tree> Trees;

#endif

