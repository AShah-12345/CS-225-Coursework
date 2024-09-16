// Pet.cpp
#include "Pet.h"
#include "Animal.h"
#include <string>
using namespace std;

string Pet::getName()
{
    return name_;
}

string Pet::getOwnerName()
{
    return owner_name_;
}


void Pet::setName(string name)
{
    name_ = name;
}

void Pet::setOwnerName(string owner)
{
    owner_name_ = owner;
}

string Pet::print()
{
    return "My name is " + name_;
}

Pet::Pet() : Animal("cat", "fish")
{
    name_ = "Fluffy";
    owner_name_ = "Cinda";
}

Pet::Pet(string type, string food, string name, string owner) : Animal(type, food)
{
    name_ = name;
    owner_name_ = owner;
}