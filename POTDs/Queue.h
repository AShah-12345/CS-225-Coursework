#pragma once
#include <vector>
#include <cstddef>

class Queue {
    public:
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
        Queue();
    private:
        int front;
        int back;
        std::vector<int> vect;
};