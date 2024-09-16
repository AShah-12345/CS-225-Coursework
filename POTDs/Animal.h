// Animal.h
#include <string>
using namespace std;
class Animal
{
    private:
        string type_;
    protected:
        string food_;
    public:
        Animal();
        Animal(string type, string food);
        string getType();
        string getFood();
        void setType(string type2);
        void setFood(string food2);
        string print();
};