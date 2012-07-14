
#ifndef TREE_H
#define TREE_H

#include "trees/TreeNode.h"
#include <ostream>

namespace ml {
namespace trees {

class Tree {
private: 
  // Disable copy and assignment. Tree can't be stored in a container, but
  // smart pointers to Tree can.
  Tree& operator=(const Tree &t);
  Tree (const Tree &t);
  
protected:
  TreeNodePtr root_;

public:
  Tree() {
    set_root(TreeNodePtr());
  }

  Tree(TreeNodePtr root) {
    set_root(root);
  }

  TreeNodePtr get_root() const {
    return root_;
  }
  
  void set_root(TreeNodePtr root) {
    root_ = root ;
  }
  
  void show(std::ostream &o = std::cout) const {
    print_subtree(root_.get(), o);
  }

  /**
   * Prints the subtree under the node root
   * @param root 
   */
  void print_subtree(Node *root, std::ostream &o ) const;

  virtual ~Tree() {};
};

typedef std::vector<Tree> Trees;
typedef std::shared_ptr<Tree> TreePtr;
typedef std::vector<TreePtr> TreePtrs;

} // trees
} // ml

#endif

