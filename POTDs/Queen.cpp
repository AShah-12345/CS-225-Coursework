#include "Queen.h"
#include <string>
using namespace std;
// implementation of class queen

Queen::Queen()
{
    type_ = "Unknown Piece Type";
    color_ = "Unknown Color";
}

string Queen::getType()
{
    return "Queen";
}