/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::update_height(Node* node) {
    node->height = std::max(heightOrNeg1(node->left), heightOrNeg1(node->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* right = t->right;
    Node* left = right->left;
    right->left = t;
    t->right = left;
    update_height(t);
    update_height(right);
    t = right;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* left = t->left;
    Node* right = left->right;
    left->right = t;
    t->left = right;
    update_height(t);
    update_height(left);
    t = left;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::height(Node* node) const
{
    if (node == nullptr) 
    {
        return 0;
    }
    return std::max(height(node->left), height(node->right)) + 1;
}

template <typename K, typename V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (!subtree) {
        return;
    }

    const int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (balance == -2) {
        const int balanceLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (balanceLeft < 0) { 
            rotateRight(subtree);
        } else { 
            rotateLeftRight(subtree);
        }
    } else if (balance == 2) {
        const int balanceRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (balanceRight > 0) {  
            rotateLeft(subtree);
        } else {  
            rotateRightLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == nullptr) 
    {
        subtree = new Node(key, value);
    } 
    else if (key < subtree->key) 
    {
        insert(subtree->left, key, value);
    } 
    else if (key > subtree->key) 
    {
        insert(subtree->right, key, value);
    } 
    else {
        subtree->value = value;
        return;
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}


template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == nullptr) {
        return;
    }

    if (key < subtree->key) {
        remove(subtree->left, key);
        subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
    } 
    else if (key > subtree->key) {
        remove(subtree->right, key);
        subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
    } 
    else {
        if (subtree->left == nullptr && subtree->right == nullptr) {
            /* no-child remove */
            delete subtree;
            subtree = nullptr;
        } 
        else if (subtree->left != nullptr && subtree->right != nullptr) {
            /* two-child remove */
            Node* predessessor = subtree->left;
            while (predessessor->right != nullptr) {
                predessessor = predessessor->right;
            }
            std::swap(subtree->key, predessessor->key);
            std::swap(subtree->value, predessessor->value);
            remove(subtree->left, predessessor->key);
            subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
            rebalance(subtree);
        } 
        else {
            /* one-child remove */
            Node* tempTree = (subtree->right == nullptr) ? subtree->left : subtree->right;
            delete subtree;
            subtree = tempTree;
            subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
            rebalance(subtree);
        }
    }
}


template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::find_min(Node* subtree) const
{
    if (subtree == nullptr)
    {
        return nullptr;
    }
    else if (subtree->left == nullptr)
    {
        return subtree;
    }
    else
    {
        return find_min(subtree->left);
    }
}