#include "TreeNode.h"

TreeNode::RotationType balanceTree(TreeNode*& subroot) {
	// Your code here
  int factor = getHeight(subroot->left_) - getHeight(subroot->right_);
  if (factor > 1) 
  {
      if (leftHeavy(subroot->left_)) 
      {
          return TreeNode::right;
      } 
      else 
      {
          return TreeNode::leftRight;
      }
  } 
  else if (factor < -1) 
  {
      if (rightHeavy(subroot->right_)) 
      {
          return TreeNode::left;
      } 
      else 
      {
          return TreeNode::rightLeft;
      }
  } 
  else 
  {
      return TreeNode::right;
  }
  return TreeNode::right;
}
