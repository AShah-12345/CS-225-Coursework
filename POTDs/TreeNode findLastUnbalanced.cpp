#include "TreeNode.h"
#include <algorithm>
TreeNode* findLastUnbalanced(TreeNode* root) {
    if (root == NULL) 
    {
      return NULL;
    }
    TreeNode* left = findLastUnbalanced(root->left_);
    TreeNode* right = findLastUnbalanced(root->right_);
    if (left != NULL || right != NULL) 
    {
        return getHeight(left) > getHeight(right) ? left : right;
    }
    if (!isHeightBalanced(root)) 
    {
        return root;
    }
    return NULL;
}

int getHeight(TreeNode* node) {
    if (node == NULL) 
    {
      return -1;
    }
    return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
}

bool isHeightBalanced(TreeNode* root) {
    if (root == NULL) return true;
    int leftHeight = getHeight(root->left_);
    int rightHeight = getHeight(root->right_);
    return std::abs(leftHeight - rightHeight) <= 1;
}



void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

