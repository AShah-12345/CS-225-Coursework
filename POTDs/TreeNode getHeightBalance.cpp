#include "TreeNode.h"
#include <algorithm>

int getHeightBalance(TreeNode* root) {
    if (root == NULL) 
    {
        return 0;
    }
    int left_height = getHeight(root->left_);
    int right_height = getHeight(root->right_);
    return left_height - right_height;
}

int getHeight(TreeNode* root) {
    if (root == NULL) 
    {
        return 0;
    }
    int left_height = getHeight(root->left_);
    int right_height = getHeight(root->right_);
    return 1 + std::max(left_height, right_height);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

