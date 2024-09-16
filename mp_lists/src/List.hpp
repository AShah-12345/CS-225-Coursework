/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  ListNode* curr = head_;
  while (curr != nullptr) 
  {
      ListNode* temp = curr;
      curr = curr->next;
      delete temp;
  }
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == nullptr)
  {
     head_ = tail_ = newNode;
  }
  else
  {
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
    /*newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;*/
  }
  int length = 0;
  for (ListNode* node = head_; node != nullptr; node = node->next) 
  {
    length++;
  }
  length_ = length;
  if(head_ == nullptr)
  {
    delete newNode;
  }
  //length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) { //switch all heads to tails
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == nullptr)
  {
     head_ = tail_ = newNode;
  }
  else
  {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
    ListNode * curr = start;
 if(start == nullptr || splitPoint <= 0)
  {
    return curr;
  }

  for (int i = 0; i < splitPoint && curr != nullptr; i++) 
  {
    curr = curr->next;
  }

  if(curr == nullptr)
  {
    return nullptr;
  }

  if (curr != nullptr) 
  {
    if(curr->prev != nullptr)
    {
      curr->prev->next = nullptr;
    }
      //if (curr->prev != NULL) 
      //{
       // curr->prev->next = NULL;
      //}
      curr->prev = nullptr; //changed
      //curr->prev = NULL; 
  }
  return curr;
}
/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (length_ < 2)
  {
    return;
  }
  ListNode *curr = head_->next;
  ListNode *temp = nullptr;
  while (curr != nullptr) 
  {
    if (curr->next != nullptr) 
    {
      temp = curr->next->next;
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      curr->prev = tail_;
      curr->next = nullptr;
      tail_->next = curr;
      tail_ = curr;
      curr = temp;
    }
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  if (head_ == nullptr || tail_ == nullptr) 
  {
    return;
  }
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if (startPoint == nullptr || endPoint == nullptr || startPoint == endPoint || startPoint->next == endPoint) 
  {
    return;
  }
  ListNode *prev = nullptr;
  ListNode *curr = startPoint;
  ListNode *previousNode = startPoint->prev;
  ListNode *nextNode = endPoint->next;
  while(curr != endPoint)
  {
      ListNode *next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
  }
  startPoint->next = nextNode;
  endPoint->next = prev;
  prev->prev = endPoint;
  curr->prev = previousNode;
  if (previousNode != nullptr) 
  {
      previousNode->next = endPoint;
  }
  else 
  {
      head_ = endPoint;
  }

  if (nextNode != nullptr) 
  {
      nextNode->prev = startPoint;
  }
  else 
  {
      tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if (n <= 0 || head_ == nullptr)
  {
      return;
  }
  ListNode *start = head_;
  ListNode *end = head_;
  while (end != nullptr)
  {
    int count = 1;
    while (count < n && end->next != nullptr)
    {
      end = end->next;
      count++;
    }
    ListNode *next_block = end->next;
    reverse(start, end);
    start->next = next_block;
    start = next_block;
    end = next_block;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != nullptr) {
        while (tail_->next != nullptr)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = nullptr;
    otherList.tail_ = nullptr;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if (first == nullptr) 
  {
    return second;
  } 
  else if (second == nullptr) 
  {
    return first;
  }
  ListNode *start;
  if (first->data < second->data) 
  {
    start = first;
    first = first->next;
  } 
  else 
  {
    start = second;
    second = second->next;
  }
  ListNode *tail = start;
  while (first != nullptr && second != nullptr) 
  {
    if (first->data < second->data) 
    {
      tail->next = first;
      first = first->next;
    } 
    else 
    {
      tail->next = second;
      second = second->next;
    }
    tail = tail->next;
  }
  if (first != nullptr) 
  {
    tail->next = first;
  } 
  else if (second != nullptr) 
  {
    tail->next = second;
  }
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
    /*if (chainLength <= 1) 
    {
        return start;
    }
    int mid = chainLength / 2;
    ListNode* left = start;
    ListNode* right = start;
    for (int i = 0; i < mid; i++) 
    {
        right = right->next;
    }
    left = mergesort(left, mid);
    right = mergesort(right, chainLength - mid);
    return merge(left, right);*/
    if (start->next == NULL) 
    {
      return start;
    }
    ListNode *second_half = split(start, chainLength / 2);
    ListNode *sorted_first_half = mergesort(start, chainLength / 2);
    ListNode *sorted_second_half = mergesort(second_half, (chainLength % 2) + (chainLength / 2));
    ListNode *sorted_list = merge(sorted_first_half, sorted_second_half);
    return sorted_list;
}