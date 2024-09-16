#include "MinHeap.h"
#include <vector>
using namespace std;
vector<int> lastLevel(MinHeap & heap)
{
        // Your code here
        vector<int> output;
        int levelSize = 1;
        int heapSize = heap.elements.size() - 1;
        while(heapSize >= levelSize)
        {
                for(int i = 0; i < levelSize; i++)
                {
                        int min = heap.pop();
                        if(i == (levelSize - 1))
                        {
                                output.push_back(min);
                        }
                }
                levelSize *= 2;
                heapSize = heap.elements.size() - 1;
        }
        return output;
}

