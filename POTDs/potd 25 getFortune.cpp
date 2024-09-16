#include <string>
using namespace std;

string getFortune(const string &s)
{
    int length = s.length();
    int fortune = length % 5;
    string fortunes[] = {"As you wish!", "Nec spe nec metu!", "Do, or do not. There is no try.", "This fortune intentionally left blank.", "Amor Fati!"};
    return fortunes[fortune];
}