#include "TreeNode.h"
#include <algorithm>


void rightRotate(TreeNode* root) {
      TreeNode* Q = root;
    TreeNode* P = Q->left_;
    Q->left_ = P->right_;
    if (P->right_ != nullptr) 
    {
        P->right_->parent_ = Q;
    }
    P->right_ = Q;
    P->parent_ = Q->parent_;
    Q->parent_ = P;
}



void leftRotate(TreeNode* root) {

    // your code here
    if (root == nullptr || root->right_ == nullptr) 
    {
        return;
    }
    TreeNode* Q = root->right_;
    TreeNode* P = root;
    P->right_ = Q->left_;
    if (Q->left_ != nullptr) 
    {
        Q->left_->parent_ = P;
    }
    Q->left_ = P;
    P->parent_ = Q;
    Q->parent_ = nullptr;
}



void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

