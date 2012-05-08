#include "trees/TreeNode.h"
#include "trees/Tree.h"
#include "utility/definitions.h"
#include "gtest/gtest.h"
#include <iostream>



void my_name2(TreeNodePtr node) {
  std::cout << "===> My name: " << node->get_name() << std::endl;
  TreeNodePtr x(new TreeNode("x"));
  x->add_child(node);
  std::cout << "x children " << x->get_number_of_children() << std::endl;
}

// Pass by reference because they are not modified
void print_ref_counts2(int step, const TreeNodePtrs &nodes) {
  std::cout << "/******* STEP  "<< step << " ********************/" << std::endl;
  TreeNodePtrs::const_iterator it = nodes.begin();
  for(it = nodes.begin(); it != nodes.end(); ++it) {
    std::cout << "name: " << (*it)->get_name()
              << " || ref count " << (*it).use_count() << std::endl;
  }
  std::cout << "/***************************/" << std::endl;
}

Ints get_ref_counts(const TreeNodePtrs &nodes) {
  Ints counts;
  TreeNodePtrs::const_iterator it = nodes.begin();
  for(it = nodes.begin(); it != nodes.end(); ++it) {
    counts.push_back(it->use_count());
  }
  return counts;
}

TEST(TestTree, NodeParent) {
  TreeNodePtr root(new TreeNode());
  Tree tree(root);
  TreeNodePtr node(new TreeNode());
  root->add_child(node);
  EXPECT_TRUE(root->get_first_child() == node);
  EXPECT_TRUE(node->get_parent() == root.get());
}

TEST(TestTreeFixture, TestReferenceCounting) {
  TreeNodePtr zero(new TreeNode("zero"));
  TreeNodePtr one(new TreeNode("one"));
  TreeNodePtr two(new TreeNode("two"));
  TreeNodePtr three(new TreeNode("three"));
  TreeNodePtr four(new TreeNode("four"));
  TreeNodePtr five(new TreeNode("five"));
  TreeNodePtr six(new TreeNode("six"));
  TreeNodePtr seven(new TreeNode("seven"));
  TreeNodePtrs nodes;
  nodes.push_back(zero);
  nodes.push_back(one);
  nodes.push_back(two);
  nodes.push_back(three);
  nodes.push_back(four);
  nodes.push_back(five);
  nodes.push_back(six);
  nodes.push_back(seven);

  Ints counts = get_ref_counts(nodes);
  int expected_counts1[8] = {2, 2, 2, 2, 2, 2, 2, 2};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts1[i], counts[i]);
  }
  
  one->add_child(zero);
  one->add_child(two);
  one->add_child(three);
  counts = get_ref_counts(nodes);
  int expected_counts2[8] = {3, 2, 3, 3, 2, 2, 2, 2};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts2[i], counts[i]);
  }

  two->add_child(four);
  counts = get_ref_counts(nodes);
  int expected_counts3[8] = {3, 2, 3, 3, 3, 2, 2, 2};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts3[i], counts[i]);
  }
  
  TreeNodePtrs children = one->get_children();
  std::vector<std::string> names;
  names.push_back("zero");
  names.push_back("two");
  names.push_back("three");
  EXPECT_EQ(names.size(), children.size());
  for (unsigned int i = 0; i < names.size(); ++i) {
    EXPECT_EQ(names[i], children[i]->get_name());
  }

  counts = get_ref_counts(nodes);
  int expected_counts4[8] = {4, 2, 4, 4, 3, 2, 2, 2};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts4[i], counts[i]);
  }

  //six->add_child(four); // This line is wrong! Four cannot have 2 parents!
  five->add_child(one);
  seven->add_child(five);
  counts = get_ref_counts(nodes);
  int expected_counts5[8] = {4, 3, 4, 4, 3, 3, 2, 2};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts5[i], counts[i]);
  }

  Tree tree(seven);
  counts = get_ref_counts(nodes);
  int expected_counts6[8] = {4, 3, 4, 4, 3, 3, 2, 3};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts6[i], counts[i]);
  }

  nodes.clear();
  counts = get_ref_counts(nodes);
  int expected_counts7[8] = {3, 2, 3, 3, 2, 2, 1, 2};
  for (unsigned int i = 0; i < nodes.size(); ++i) {
    EXPECT_EQ(expected_counts7[i], counts[i]);
  }
}

