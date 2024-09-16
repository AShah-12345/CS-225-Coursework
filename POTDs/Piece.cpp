#include "Piece.h"
#include <string>
using namespace std;
// implementation of class piece
Piece::Piece()
{
    type_ = "Unknown Piece Type";
    color_ = "Unknown Color";
}

string Piece::getType() 
{
    return "Unknown Piece Type";
}