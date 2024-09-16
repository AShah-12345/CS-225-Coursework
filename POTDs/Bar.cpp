// your code here
#include <string>
using namespace std;
#include "Bar.h"
#include "Foo.h"

potd::Bar::Bar()
{
    f_ = new Foo(" ");
}

potd::Bar::Bar(string b)
{
    f_ = new Foo(b);
}

potd::Bar::Bar(const Bar &b)
{
    f_ = new Foo(b.f_->get_name());
}

potd::Bar::~Bar()
{
    delete f_;
}

potd::Bar & potd::Bar::operator=(const Bar &b) 
{
    if (this != &b) {
        delete f_;
        f_ = new Foo(b.f_->get_name());
    }
    return *this;
}

string potd::Bar::get_name() {
    return f_->get_name();
}