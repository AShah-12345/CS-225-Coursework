#include <vector>
#include "Primes.h"

std::vector<int> *genPrimes(int M) {
    std::vector<int> *v = new std::vector<int>();
    std::vector<int> *t = new std::vector<int>(M);
    int i=0;
    int nextPrime = 2;

    for(i=0; i<M; i++)
        (*t)[i] = 1;

    (*t)[0]=0;
    (*t)[1]=0;

    v->push_back(2);

    while (nextPrime < M) {
        for(i=nextPrime*nextPrime;
                i < M;
                i+=nextPrime)
            (*t)[i] = 0;
        for(++nextPrime; nextPrime<M; nextPrime++)
            if ((*t)[nextPrime] == 1) {
                v->push_back(nextPrime);
                break;
            }
    }

    delete t;
    return v;
}


int numSequences(std::vector<int> *primes, int num) {

    // your code here
   int count = 0;
    for (std::vector<int>::size_type i = 0; i < primes->size(); i++) {
        int sum = 0;
        for (std::vector<int>::size_type j = i; j < primes->size(); j++) {
            sum += (*primes)[j];
            if (sum == num) {
                count++;
                break;
            }
            if (sum > num) {
                break;
            }
        }
    }

    return count;
}
    // code to quell compiler complaints.  Delete it.
    //return num + (*primes)[1];
//}
