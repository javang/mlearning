#include "gtest/gtest.h"
#include "trees/TreeNode.h"
#include "trees/Tree.h"
#include "core/definitions.h"
#include <iostream>
#include <algorithm>

Ints get_ref_counts(const NodePtrs &nodes) {
  Ints counts;
  NodePtrs::const_iterator it = nodes.begin();
  for(it = nodes.begin(); it != nodes.end(); ++it) {
    counts.push_back(it->use_count());
  }
  return counts;
}

TEST(TestTree, NodeParent) {
  TreeNodePtr root(new TreeNode());
  Tree tree(root);
  NodePtr node(new TreeNode());
  root->add_child(node);
  EXPECT_TRUE(root->get_first_child() == node);
  EXPECT_TRUE(node->get_parent() == root.get());
}

TEST(TestTree, TestSibling) {
  NodePtr root(new TreeNode());
  NodePtr x(new TreeNode());
  NodePtr y(new TreeNode());
  root->add_child(x);
  root->add_child(y);
  EXPECT_EQ(x->get_parent(), y->get_parent());
  EXPECT_EQ(x->get_next_sibling(), y);
}


TEST(TestTreeFixture, TestReferenceCounting) {
  NodePtr zero(new TreeNode("zero"));
  NodePtr one(new TreeNode("one"));
  NodePtr two(new TreeNode("two"));
  NodePtr three(new TreeNode("three"));
  NodePtr four(new TreeNode("four"));
  NodePtr five(new TreeNode("five"));
  NodePtr six(new TreeNode("six"));
  NodePtr seven(new TreeNode("seven"));
  NodePtrs nodes;
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
  
  NodePtrs children = one->get_children();
  Strings names;
  names.push_back("zero");
  names.push_back("two");
  names.push_back("three");
  EXPECT_EQ(names.size(), children.size());
  Strings::iterator s = names.begin();
  for (NodePtrs::iterator i = children.begin(); i != children.end(); ++i, ++s) {
    EXPECT_EQ(*s, (*i)->get_name());
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

  Tree tree(std::dynamic_pointer_cast<TreeNode>(seven));
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

