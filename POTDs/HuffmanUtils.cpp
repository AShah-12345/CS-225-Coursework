#include "HuffmanNode.h"
#include "HuffmanUtils.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <stack>
using std::string;

/**
 * binaryToString
 *
 * Write a function that takes in the root to a huffman treex
 * and a binary string.
 *
 * Remember 0s in the string mean left and 1s mean right.
 */

string binaryToString(string binaryString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    string output;
    HuffmanNode *curr = huffmanTree;
    for(char c : binaryString)
    {
        if(c == '0')
        {
            curr = curr->left_;
        }
        else
        {
            curr = curr->right_;
        }
        if(curr->left_ == nullptr && curr->right_ == nullptr)
        {
            output += curr->char_;
            curr = huffmanTree;
        }
    }
    return output;
}

/**
 * stringToBinary
 *
 * Write a function that takes in the root to a huffman tree
 * and a character string. Return the binary representation of the string
 * using the huffman tree.
 *
 * Remember 0s in the binary string mean left and 1s mean right
 */

map<char, string> stringToBinaryMap(HuffmanNode* root) {
    map<char, string> map;
    stack<pair<HuffmanNode*, string>> stack;
    stack.push(make_pair(root, ""));
    
    while (!stack.empty()) {
        HuffmanNode* node = stack.top().first;
        string code = stack.top().second;
        stack.pop();
        
        if (node->left_ == nullptr && node->right_ == nullptr) {
            map[node->char_] = code;
        } else {
            if (node->left_ != nullptr) {
                stack.push(make_pair(node->left_, code + "0"));
            }
            if (node->right_ != nullptr) {
                stack.push(make_pair(node->right_, code + "1"));
            }
        }
    }
    
    return map;
}

string stringToBinary(string charString, HuffmanNode* huffmanTree) {
    map<char, string> map = stringToBinaryMap(huffmanTree);
    string output;
    for (char c : charString) 
    {
        output += map[c];
    }
    return output;
}


