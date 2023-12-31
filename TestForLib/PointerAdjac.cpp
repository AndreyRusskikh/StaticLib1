#include "PointerAdjac.h"

PointerAdjac::PointerAdjac(AdjacencyMatrix* p)
{
    ptr = p;
    count = 0;
}
AdjacencyMatrix* PointerAdjac::operator -> ()
{
    count++;
    std::cout << "The pointer worked in " << count << " times\n";
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