#include "PointerAdjac.h"

PointerAdjac::PointerAdjac(AdjacencyMatrix* p)
{
    ptr = p;
    count = 1;
}
AdjacencyMatrix* PointerAdjac::operator -> ()
{
    count++;
    std::cout << "”казатель сработал!\n";
    return ptr;
}
PointerAdjac::~PointerAdjac()
{
    if (ptr != nullptr) delete ptr;
}
int PointerAdjac::get_count()
{
    return count;
}