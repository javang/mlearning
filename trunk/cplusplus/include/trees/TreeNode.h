
#ifndef TREENODE_H
#define TREENODE_H

//#include "utility/errors.h"
#include "core/definitions.h"
#include "trees/Node.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

class TreeNode;
typedef std::shared_ptr< TreeNode > TreeNodePtr;
typedef std::vector< TreeNodePtr > TreeNodePtrs;


class TreeNode: public Node {

private:
  void init();
  
protected:
  String name_;
  // NodePtr applies because the parent owns the children. They must be
  // living if the parent is using them
  NodePtr first_child_;
  NodePtr next_sibling_;
  // A node does not share its parent. No NodePtr required. Using it is an mistake
  Node *parent_;

public:
  TreeNode() {
    name_ = "";
    init();
  };

  TreeNode(const String &name) {
    parent_ = nullptr;
    name_ = name;
    init();
  };

  TreeNode(Node *parent, NodePtr first_child, NodePtr next_sibling);

  NodePtr get_first_child() const {
    return first_child_;
  }
  void set_first_child(NodePtr t) {
    first_child_ = t;
  }

  NodePtr get_next_sibling() const {
    return next_sibling_;
  }
  void set_next_sibling(NodePtr t) {
    next_sibling_ = t;
  }

  Node* get_parent() const {
    return parent_;
  }
  void set_parent(Node *t) {
    if(parent_ != nullptr) {
//      throw WrongParent("Only one parent per node is allowed");
    }
    parent_ = t;
  }

  String get_name() const {
    return name_;
  }
  void set_name(const String &name) {
    name_ = name;
  }

  void add_child(NodePtr node);

  NodePtrs get_children();


  unsigned int get_number_of_children() const;

  virtual ~TreeNode() {
    // std::cout << " I am dying: " << name_ << std::endl;
  }

  void show(std::ostream &o) const {
    //o << "caca" << std::endl;
    //o << "My name is :" << name_ << std::endl;
  };

  void remove_child(int i) {
    // TODO
  }
  
  bool is_leaf() const;
};



#endif

