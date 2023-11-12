#include "PointerAdjac.h"

PointerAdjac::PointerAdjac(AdjacencyMatrix* p) : ptr(p), count(1) {}

AdjacencyMatrix* PointerAdjac::operator->()
{
    return ptr;
}

PointerAdjac::~PointerAdjac()
{
    count--;
    if (count == 0)
    {
        delete ptr;
    }
}

int PointerAdjac::get_count()
{
    return count;
}
