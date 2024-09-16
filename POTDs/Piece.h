#pragma once
#include <string>
using namespace std;
class Piece {
    private:
        string type_;
        string color_;
    public:
        string getType();
        Piece();
};
