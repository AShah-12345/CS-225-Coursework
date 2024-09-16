#include "potd.h"
#include <vector>
using namespace std;
double sum(vector<double>::iterator start, vector<double>::iterator end)
{
    double sum = 0;
    for(auto i = start; i != end; i++)
    {
        sum += *i;
    }
    return sum;
}

vector<double>::iterator max_iter(vector<double>::iterator start, vector<double>::iterator end)
{
    vector<double>::iterator target = start;
    double curr = *start;
    for(auto i = start; i != end; i++)
    {
        if(*i > curr)
        {
            curr = *i;
            target = i;
        }
    }
    return target;
}

void sort_vector(vector<double>::iterator start, vector<double>::iterator end)
{
    for (auto i = start; i != end; ++i) 
    {
        auto max = max_iter(i, end);
        if (max != i) 
        {
            iter_swap(i, max);
        }
    }
} 