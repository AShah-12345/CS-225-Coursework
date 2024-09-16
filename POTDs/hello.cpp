#include <iostream>
#include <string>
using namespace std;

 int your_age; //var for age
 std::string your_name; //var for name

    std::string hello()
    {
        your_age = 19; //init age
        your_name = "Aryan"; //init name
        return "Hello world! My name is " + your_name + " and I am " + std::to_string(your_age) + " years old.";
    }