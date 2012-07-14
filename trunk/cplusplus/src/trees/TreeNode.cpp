
#include "trees/TreeNode.h"
using namespace ml;
using namespace ml::trees;

void TreeNode::init() {
  first_child_ = NodePtr();
  next_sibling_ = NodePtr();
  parent_ = nullptr;
}

TreeNode::TreeNode(Node *parent, NodePtr first_child,
                                       NodePtr next_sibling) {
  first_child_ = first_child;
  next_sibling_ = next_sibling;
  parent_ = parent;
}


void TreeNode::add_child(NodePtr node) {
  if(first_child_ == 0) {
    first_child_ = std::dynamic_pointer_cast<TreeNode>(node);
  } else {
    NodePtr current = first_child_;
    NodePtr sibling = current->get_next_sibling();
    while(sibling != 0) {
      current = sibling;
      sibling = current->get_next_sibling();
    }
    current->set_next_sibling(node);
  }
  node->set_parent(this);
}

NodePtrs TreeNode::get_children() {
  NodePtrs children;
  NodePtr sibling = first_child_;
  while (sibling != 0) {
    children.push_back(sibling);
    sibling = sibling->get_next_sibling();
  }
  return children;
}

unsigned int TreeNode::get_number_of_children() const {
  unsigned int n = 0;
  NodePtr sibling = first_child_;
  while(sibling != 0) {
    n++;
    sibling = sibling->get_next_sibling();
  }
  return n;
}

bool TreeNode::is_leaf() const {
 return first_child_ == 0; 
}


