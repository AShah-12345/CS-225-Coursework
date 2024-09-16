#include "Queue.h"
#include <vector>
Queue::Queue() { 
  front=0;
  back=-1;
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const {
  return back - front + 1;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
  return (back < front);
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value) {
    back++;
    vect.push_back(value);
}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
  if(isEmpty())
  {
    return 0;
  }
  int temp = vect[front];
  front++;
  return temp;
}
