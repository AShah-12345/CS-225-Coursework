// your code here
#include "Food.h"
#include "q5.h"
void increase_quantity(Food* f)
{
    f->set_quantity(f->get_quantity() + 1);
}