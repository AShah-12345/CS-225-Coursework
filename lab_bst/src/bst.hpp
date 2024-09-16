/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <vector>
#include <queue>


template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* current = root;
    while (current != nullptr) 
    {
        if (current->key == key) 
        {
            return current->value;
        }
        else if (key < current->key) 
        {
            current = current->left;
        } else
        {
            current = current->right;
        }
    }
    return V();
}

template <class K, class V>
typename BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if(subtree == nullptr || subtree->key == key)
    {
        return subtree;
    }
    if(key < subtree->key)
    {
        return find(subtree->left, key);
    }
    return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    Node *& node = find(root, key); 
    if (node == nullptr) 
    { 
        node = new Node(key, value);
    } 
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
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
    else 
    { 
        subtree->value = value;
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    Node* temp = first;
    first = second;
    second = temp;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == nullptr) 
    { 
        return;
    } 
    else if (key < subtree->key) 
    { 
        remove(subtree->left, key);
    } 
    else if (key > subtree->key) 
    { 
        remove(subtree->right, key);
    } 
    else 
    { 
        if (subtree->left == nullptr && subtree->right == nullptr) 
        { 
            delete subtree;
            subtree = nullptr;
        } 
        else if (subtree->left == nullptr) 
        { 
            Node* temp = subtree;
            subtree = subtree->right;
            delete temp;
        } 
        else if (subtree->right == nullptr) 
        { 
            Node* temp = subtree;
            subtree = subtree->left;
            delete temp;
        } 
        else 
        {
            Node* successorParent = subtree;
            Node* successor = subtree->right;
            while (successor->left != nullptr) 
            {
                successorParent = successor;
                successor = successor->left;
            }
            subtree->key = successor->key;
            subtree->value = successor->value;
            if (successor == subtree->right)
            {
                subtree->right = successor->right;
            }
            else
            {
                successorParent->left = successor->right;
            }
            delete successor;
        }
    }
}


template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> tree;
    for (auto const& pair : inList) 
    {
        tree.insert(pair.first, pair.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> data) {
    BST<K, V> tree = listBuild(data);
    std::vector<K> temp = tree.getInorderTraversal();
    std::vector<int> hist(temp.size());
    std::vector<std::pair<K, int>> list(temp.size());
    for (unsigned int i = 0; i < temp.size(); i++) 
    {
        list[i] = {temp[i], 0};
    }
    do {
        for (unsigned int i = 0; i < temp.size(); i++) 
        {
            list[i].first = temp[i];
            list[i].second = 0;
        }
        BST<K, V> t = listBuild(list);
        hist[t.height()]++;
    } while (std::next_permutation(temp.begin(), temp.end()));
    return hist;
}