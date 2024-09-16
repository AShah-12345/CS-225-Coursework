// your code here
#include <string>
using namespace std;
#include "Foo.h"
#pragma once
namespace potd
{
    class Bar
    {
        private:
            Foo *f_;
        public:
            Bar();
            Bar(string b);
            Bar(const Bar &b);
            ~Bar();
            Bar &operator=(const Bar &b);
            string get_name();
    };
}