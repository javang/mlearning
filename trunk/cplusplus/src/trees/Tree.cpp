
#include "trees/Tree.h"
#include <algorithm>
using namespace ml;
using namespace ml::trees;
        
void Tree::print_subtree(Node *node, std::ostream &o) const {
  if(node != 0) {
    node->show(o);
    
    NodePtrs children = node->get_children();
    for(NodePtrs::iterator i = children.begin();i != children.end(); ++i) {
      o << "===========>" << std::endl;
      print_subtree((*i).get(), o);
    }
  }
}

