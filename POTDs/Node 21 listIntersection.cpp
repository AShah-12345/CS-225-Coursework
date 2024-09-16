#include "Node.h"
#include <stack>
using namespace std;

Node* listIntersection(Node* first, Node* second) 
{
    Node* intersection = nullptr;
    Node** curr = &intersection;
    
    while (first != nullptr) {
        Node* temp = second;
        bool found = false;
        while (temp != nullptr) {
            if (temp->data_ == first->data_) {
                found = true;
                break;
            }
            temp = temp->next_;
        }
        if (found) {
            *curr = new Node();
            (*curr)->data_ = first->data_;
            (*curr)->next_ = nullptr;
            curr = &((*curr)->next_);
        }
        first = first->next_;
    }
    
    return intersection;
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
