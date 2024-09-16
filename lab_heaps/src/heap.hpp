
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0; //chose root of index 0
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return ((2*currentIdx) + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return ((2*currentIdx) + 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
     return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t leftIdx = leftChild(currentIdx);
    size_t rightIdx = rightChild(currentIdx);
    if (rightIdx >= _elems.size() || higherPriority(_elems[leftIdx], _elems[rightIdx])) 
    {
        return leftIdx;
    } 
    else 
    {
        return rightIdx;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    size_t leftChildIdx = leftChild(currentIdx);
    size_t rightChildIdx = rightChild(currentIdx);
    size_t highestPriorityIdx = currentIdx;
    if (leftChildIdx < _elems.size() && higherPriority(_elems[leftChildIdx], _elems[highestPriorityIdx])) 
    {
        highestPriorityIdx = leftChildIdx;
    }
    if (rightChildIdx < _elems.size() && higherPriority(_elems[rightChildIdx], _elems[highestPriorityIdx])) 
    {
        highestPriorityIdx = rightChildIdx;
    }
    if (highestPriorityIdx != currentIdx) 
    {
        std::swap(_elems[currentIdx], _elems[highestPriorityIdx]);
        heapifyDown(highestPriorityIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() : _elems()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) : _elems(elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    size_t startIdx = parent(elems.size() - 1);
    for (size_t i = startIdx; i > 0; i--) 
    {
        heapifyDown(i);
    }
    if (elems.size() > 0) 
    {
        heapifyDown(0);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (_elems.empty()) 
    {
        return T();
    }
    T root = _elems[0];
    _elems[0] = _elems.back();
    _elems.pop_back();
    if (!_elems.empty()) 
    {
        heapifyDown(0);
    }
    return root;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    size_t currentIdx = _elems.size() - 1;
    heapifyUp(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    size_t parentIdx = parent(idx);
    if (idx != 0 && higherPriority(_elems[idx], _elems[parentIdx])) 
    {
        heapifyUp(idx);
    }
    else 
    {
        heapifyDown(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == 0;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}