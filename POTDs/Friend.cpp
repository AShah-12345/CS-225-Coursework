#include "Friend.h"
#include <vector>
int find(int x, std::vector<int>& parents) {
   // your code
   if(parents[x] == -1 || parents[x] == x)
   {
       return x;
   }
   return parents[x] = find(parents[x], parents);
}

int findCircleNum(std::vector<std::vector<int>>& M) {
    // your code
     int n = M.size();
    std::vector<int> parents(n, -1);
    int count = n;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (M[i][j] == 1) {
                int p1 = find(i, parents);
                int p2 = find(j, parents);
                if (p1 != p2) {
                    parents[p1] = p2;
                    count--;
                }
            }
        }
    }
    return count;
}


