#include "Node.h"
Node *insertSorted(Node *first, int data) {
    Node *newNode = new Node;
    newNode->data_ = data;
    newNode->next_ = nullptr;

    if (first == nullptr || data < first->data_) {
        newNode->next_ = first;
        return newNode;
    } else {
        Node *curr = first;
        while (curr->next_ != nullptr && data > curr->next_->data_) {
            curr = curr->next_;
        }
        newNode->next_ = curr->next_;
        curr->next_ = newNode;
        return first;
    }
}

Node *listUnion(Node *first, Node *second) {
    Node *out = nullptr;
    Node *last = nullptr;
    while (first != nullptr) 
    {
        out = insertSorted(out, first->data_);
        if (last == nullptr) 
        {
            last = out;
        } else 
        {
            while (last->next_ != nullptr) 
            {
                last = last->next_;
            }
        }
        first = first->next_;
    }
    while (second != nullptr) 
    {
        out = insertSorted(out, second->data_);
        second = second->next_;
    }
    Node *curr = out;
    while (curr != nullptr && curr->next_ != nullptr) 
    {
        if (curr->data_ == curr->next_->data_) 
        {
            Node *temp = curr->next_;
            curr->next_ = curr->next_->next_;
            delete temp;
        } 
        else 
        {
            curr = curr->next_;
        }
    }
    return out;
}

Node::Node() {
    numNodes++;
}

Node::Node(const Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;