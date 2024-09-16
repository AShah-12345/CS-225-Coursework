#include <string>
#pragma once
namespace potd
{
    class Student 
{
    private:
        std::string name_;
        int grade_;
    public:
        Student();
        std::string get_name();
        void set_name(std::string name);
        int get_grade();
        void set_grade(int grade);
    };
}