#include <string>
#include "Base.h"
#pragma once
class Derived : public Base
{
    public:
        std::string foo();
        virtual std::string bar();
        virtual ~Derived();
};