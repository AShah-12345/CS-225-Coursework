// Your code here! :)
#include <string>
#include "student.h"
#pragma once
using namespace std;

potd::Student::Student()
{
    name_ = "Sally";
    grade_ = 5;
}

string potd::Student::get_name()
{
    return name_;
}

int potd::Student::get_grade()
{
    return grade_;
}

void potd::Student::set_name(string name)
{
    name_ = name;Opp
}

void potd::Student::set_grade(int grade)
{
    grade_ = grade;
}