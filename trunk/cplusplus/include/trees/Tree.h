
#ifndef TREE_H
#define TREE_H

#include "trees/TreeNode.h"

class Tree {
private: 
  // Disable copy and assignment
  Tree operator=(Tree &t);
  Tree (Tree &t);
  
protected:
  TreeNodePtr root_;

public:
  Tree() {
    set_root(TreeNodePtr());
  }

  Tree(TreeNodePtr root) {
    set_root(root);
  }

  void set_root(TreeNodePtr root) {
    root_ = root ;
  }
  
  void print_tree() const {
    print_subtree(root_);
  }

  /**
   * Prints the subtree under the node root
   * @param root 
   */
  void print_subtree(TreeNodePtr root) const;

  virtual ~Tree() {};
};

typedef std::vector<Tree> Trees;
typedef std::shared_ptr<Tree> TreePtr;
typedef std::vector<TreePtr> TreePtrs;

#endif

