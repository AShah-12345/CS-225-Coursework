#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int TreeNode::getHeight() {
  if (this == NULL) 
    return -1;
  return 1 + std::max(this->left_->getHeight(), this->right_->getHeight());
}
