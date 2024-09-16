/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;
void DisjointSets::addelements(int num)
{
    for(int i = 0; i < num; i++)
    {
        set_.push_back(-1);
    }
    num_sets_ += num;
}

int DisjointSets::find(int elem)
{
    if (set_[elem] < 0) 
    {
        return elem;
    } 
    else 
    {
        int root = find(set_[elem]);
        set_[elem] = root;
        return root;
    }
}

void DisjointSets::setunion(int a, int b)
{
    int roota = find(a);
    int rootb = find(b);
    if (set_[roota] < set_[rootb]) 
    {
        setunionHelper(roota, rootb);
    } 
    else 
    {
        setunionHelper(rootb, roota);
    }
    num_sets_--;
}

void DisjointSets::setunionHelper(int a, int b)
{
    set_[a] += set_[b];
    set_[b] = a;
}

int DisjointSets::size(int elem)
{
    int root = find(elem);
    return -set_[root];
}
