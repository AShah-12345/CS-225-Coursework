#include "Node.h"
#include <unordered_set>
using namespace std;

Node* listSymmetricDifference(Node* first, Node* second) {
    unordered_set<int> firstSet;
    unordered_set<int> secondSet;
    Node* output = nullptr;
    Node** curr = &output;
    unordered_set<int> outputSet;
    for (Node* node = first; node != nullptr; node = node->next_) 
    {
        firstSet.insert(node->data_);
    }
    for (Node* node = second; node != nullptr; node = node->next_) 
    {
        secondSet.insert(node->data_);
    }
    for (Node* node = first; node != nullptr; node = node->next_) 
    {
        if (firstSet.count(node->data_) == 1 && secondSet.count(node->data_) == 0 && outputSet.count(node->data_) == 0) 
        {
            *curr = new Node();
            (*curr)->data_ = node->data_;
            (*curr)->next_ = nullptr;
            curr = &((*curr)->next_);
            outputSet.insert(node->data_);
        }
    }
    for (Node* node = second; node != nullptr; node = node->next_) 
    {
        if (secondSet.count(node->data_) == 1 && firstSet.count(node->data_) == 0 && outputSet.count(node->data_) == 0) 
        {
            *curr = new Node();
            (*curr)->data_ = node->data_;
            (*curr)->next_ = nullptr;
            curr = &((*curr)->next_);
            outputSet.insert(node->data_);
        }
    }
    return output;
}



Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
