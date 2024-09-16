#include "TreeNode.h"
#include <algorithm>
bool isHeightBalanced(TreeNode* root) {
  if (root == NULL) 
  {
      return true;
  }
    int left_height = height(root->left_);
    int right_height = height(root->right_);
    if (std::abs(left_height - right_height) > 1) 
    {
        return false;
    }
    return isHeightBalanced(root->left_) && isHeightBalanced(root->right_);
}

int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return std::max(height(root->left_), height(root->right_)) + 1;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

