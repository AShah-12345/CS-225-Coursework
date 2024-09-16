// Your code here
#include <string>
#include "Food.h"
using namespace std;

Food::Food() 
{
    name_ = "apples";
    quantity_ = 5;
}
string Food::get_name()
{
    return name_;
}
void Food::set_name(string name) 
{
    name_ = name;
}
int Food::get_quantity() 
{
    return quantity_;
}
void Food::set_quantity(int quantity) 
{
    quantity_ = quantity;
}