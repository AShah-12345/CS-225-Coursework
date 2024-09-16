#include "Node.h"

using namespace std;

void sortList(Node **head) 
{

    Node *curr = *head;
    int count = 0;
    while(curr != nullptr)
    {
        count++;
        curr = curr->next_;
    }
    for(int i = 0; i < count - 1; i++)
    {
        curr = *head; //reset
        Node *prev = nullptr;
        for(int j = 0; j < count - i - 1; j++)
        {
            if(curr->data_ > curr->next_->data_)
            {
                if(prev == nullptr)
                {
                    *head = curr->next_;
                }
                else
                {
                    prev->next_ = curr->next_;
                }
                Node *temp = curr->next_->next_;
                curr->next_->next_ = curr;
                curr->next_ = temp;

                prev = curr->next_;
            } 
            else 
            {
                prev = curr;
                curr = curr->next_;
            }
        }
    }    
}

/*void swap(Node *one, Node *two) //helper swap function for Bubble Sort
{
    int temp = one->data_;
    one->data_ = two->data_;
    two->data_ = temp;
}*/

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

