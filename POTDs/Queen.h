#pragma once
#include "Piece.h"
class Queen : public Piece
{
    private:
        string type_;
        string color_;
    public:
        string getType();
        Queen();
};