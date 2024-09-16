// Animal.cpp
#include <string>
using namespace std;
#include "Animal.h"

Animal::Animal()
{
    type_ = "cat";
    food_ = "fish";
}

Animal::Animal(string type, string food)
{
    type_ = type;
    food_ = food;
}

string Animal::getType()
{
    return type_;
}

string Animal::getFood()
{
    return food_;
}

void Animal::setType(string type2)
{
    type_ = type2;
}

void Animal::setFood(string food2)
{
    food_ = food2;
}

string Animal::print()
{
    string output = "I am a " + type_ + ".";
    return output;
}