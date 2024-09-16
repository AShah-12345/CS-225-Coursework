
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListIterator temp(*this);
        position_ = position_->next;
        return temp;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if (position_ != nullptr && position_->prev != nullptr) //added
        {
            position_ = position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        ListIterator temp(*this);
        if (position_ != nullptr && position_->prev != nullptr) //added
        {
            position_ = position_->prev;
        }
        return temp;
    }

    bool operator!=(const ListIterator& rhs) {
        if(position_ != rhs.position_)
        {
            return true;
        }
        return false;
    }

    bool operator==(const ListIterator& rhs) {
          if(position_ == rhs.position_)
        {
            return true;
        }
        return false;
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
