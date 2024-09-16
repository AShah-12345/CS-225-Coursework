// Pet.h
#pragma once
#include "Animal.h"
#include <string>
using namespace std;

class Pet : public Animal
{
    private:
        string name_;
        string owner_name_;
    public:
        string getName();
        string getOwnerName();
        void setName(string);
        void setOwnerName(string);
        string print();
        Pet();
        Pet(string, string, string, string);
};