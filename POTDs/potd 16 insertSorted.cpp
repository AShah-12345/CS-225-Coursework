#include "potd.h"
#include <iostream>

using namespace std;

void insertSorted(Node **head, Node *insert) {
  Node **curr = head;
  while(*curr != NULL && (insert->data_ > (*curr)->data_))
  {
    curr = &(*curr)->next_;
  }
  insert->next_ = *curr;
  *curr = insert;
}
