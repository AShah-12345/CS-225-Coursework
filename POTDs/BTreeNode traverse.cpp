#include <vector>
#include "BTreeNode.h"


std::vector<int> traverse(BTreeNode* root) {
    std::vector<int> v;
    if (root != nullptr) {
        if (!root->is_leaf_) {
            for (unsigned i = 0; i < root->elements_.size(); i++) {
                std::vector<int> left_ = traverse(root->children_[i]);
                v.insert(v.end(), left_.begin(), left_.end());
                v.push_back(root->elements_[i]);
            }
            std::vector<int> right_ = traverse(root->children_.back());
            v.insert(v.end(), right_.begin(), right_.end());
        } else {
            v.insert(v.end(), root->elements_.begin(), root->elements_.end());
        }
    }
    return v;
}

