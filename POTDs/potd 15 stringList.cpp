#include "potd.h"
#include <iostream>

using namespace std;

string stringList(Node *head) 
{
    string result;
    int count = 0;
    Node *curr = head;
    if(curr == NULL)
    {
        return "Empty list";
    }
    while(curr != NULL)
    {
        result = result + ("Node " + to_string(count) + ": " + to_string(curr->data_));
        count++;
        if(curr->next_ != NULL)
        {
            result = result + " -> ";
        }
        curr = curr->next_;
    }
    return result;
}
