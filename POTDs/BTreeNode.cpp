#include <vector>
#include "BTreeNode.h"


BTreeNode* find(BTreeNode* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < root->elements_.size(); i++) {
        if (root->elements_[i] == key) {
            return root;
        }
    }

    for (BTreeNode* child : root->children_) {
        BTreeNode* result = find(child, key);
        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}

