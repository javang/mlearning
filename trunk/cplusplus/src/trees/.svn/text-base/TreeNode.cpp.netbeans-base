
#include "trees/TreeNode.h"


void TreeNode::init() {
  first_child_ = TreeNodePtr();
  next_sibling_ = TreeNodePtr();
  parent_ = NULL;
}

TreeNode::TreeNode(TreeNode* parent, TreeNodePtr first_child,
                   TreeNodePtr next_sibling) {
  first_child_ = first_child;
  next_sibling_ = next_sibling;
  parent_ = parent;
}


void TreeNode::add_child(TreeNodePtr node) {
  if(first_child_ == 0) {
    first_child_ = node;
  } else {
    TreeNodePtr current = first_child_;
    TreeNodePtr sibling = current->get_next_sibling();
    while(sibling != 0) {
      current = sibling;
      sibling = current->get_next_sibling();
    }
    current->set_next_sibling(node);
  }
  node->set_parent(this);
}

TreeNodePtrs TreeNode::get_children() {
  TreeNodePtrs children;
  TreeNodePtr sibling = first_child_;
  while (sibling != 0) {
    children.push_back(sibling);
    sibling = sibling->get_next_sibling();
  }
  return children;
}

unsigned int TreeNode::get_number_of_children() const {
  unsigned int n = 0;
  TreeNodePtr sibling = first_child_;
  while(sibling != 0) {
    n++;
    sibling = sibling->get_next_sibling();
  }
  return n;
}




