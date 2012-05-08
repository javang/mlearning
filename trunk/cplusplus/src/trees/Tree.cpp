
#include "trees/Tree.h"
#include <algorithm>

void Tree::print_subtree(TreeNodePtr node) const {
  if(node != nullptr) {
    node->show();
    TreeNodePtrs children = node->get_children();
    for(TreeNodePtrs::iterator it = children.begin();
                                            it != children.end(); ++it) {
      print_subtree(*it);
    }
  }
}

