
#ifndef TREENODE_H
#define TREENODE_H

#include "utility/errors.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

class TreeNode;
typedef std::shared_ptr< TreeNode > TreeNodePtr;
typedef std::vector< TreeNodePtr > TreeNodePtrs;


class TreeNode {

private:
  void init();
  TreeNode operator=(TreeNode T);
  TreeNode(TreeNode &T);
  
protected:
  std::string name_;
  // TreeNodePtr applies because the parent owns the children. They must be
  // living if the parent is using them
  TreeNodePtr first_child_;
  TreeNodePtr next_sibling_;
  // A node does not share its parent. No TreeNodePtr required. Using it is an mistake
  TreeNode *parent_;

  
public:
  TreeNode() {
    init();
  };

  TreeNode(const std::string &name) {
    parent_ = nullptr;
    name_ = name;
    init();
  };

  TreeNode(TreeNode *parent, TreeNodePtr first_child, TreeNodePtr next_sibling);

  TreeNodePtr get_first_child() const {
    return first_child_;
  }
  void set_first_child(TreeNodePtr t) {
    first_child_ = t;
  }

  TreeNodePtr get_next_sibling() const {
    return next_sibling_;
  }
  void set_next_sibling(TreeNodePtr t) {
    next_sibling_ = t;
  }

  TreeNode* get_parent() const {
    return parent_;
  }
  void set_parent(TreeNode *t) {
    if(parent_ != nullptr) {
      throw WrongParent("Only one parent per node is allowed");
    }
    parent_ = t;
  }

  std::string get_name() const {
    return name_;
  }
  void set_name(const std::string &name) {
    name_ = name;
  }

  void add_child(TreeNodePtr node);

  TreeNodePtrs get_children();


  unsigned int get_number_of_children() const;

  virtual ~TreeNode() {
    // std::cout << " I am dying: " << name_ << std::endl;
  }

  void show() const {
    std::cout << "My name is :" << name_ << std::endl;
  };

  void remove_child(int i) {
    // TODO
  }
  
  bool is_leaf() const;
};

#endif

