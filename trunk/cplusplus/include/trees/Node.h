/* 
 * File:   node.h
 * Author: javi
 *
 * Created on July 1, 2012, 9:09 AM
 */

#ifndef NODE_H
#define	NODE_H


#include "core/definitions.h"
#include <vector>
#include <iostream>
#include <memory>

class Node;
typedef std::shared_ptr< Node > NodePtr;
typedef std::vector< NodePtr > NodePtrs;

class Node {
private:
  Node &operator=(const Node &T);
  Node(const Node &T);
public:
  
  Node() {}
  virtual ~Node() {} 
  virtual NodePtr get_first_child() const = 0;
  virtual void set_first_child(NodePtr t) = 0;
  virtual NodePtr get_next_sibling() const = 0;
  virtual void set_next_sibling(NodePtr t) = 0;
  virtual Node* get_parent() const = 0;
  virtual void set_parent(Node *t) = 0;
  virtual void add_child(NodePtr node) = 0;
  virtual NodePtrs get_children() = 0;
  virtual unsigned int get_number_of_children() const = 0;
  virtual bool is_leaf() const = 0;
  virtual void show(std::ostream &o) const = 0;
  virtual String get_name() const = 0;
  virtual void set_name(const String &name) = 0;
};  
    

#endif	/* NODE_H */

