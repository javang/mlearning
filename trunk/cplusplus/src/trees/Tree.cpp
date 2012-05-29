
#include "trees/Tree.h"
#include <algorithm>

void Tree::print_subtree(TreeNode *node, std::ostream &o) const {
  if(node != 0) {
    node->show(o);
    
    TreeNodePtrs children = node->get_children();
    for(TreeNodePtrs::iterator it = children.begin();
                                            it != children.end(); ++it) {
      o << "===========>" << std::endl;
      print_subtree((*it).get(), o);
    }
  }
}

