#include "PointerIncid.h"

PointerIncid::PointerIncid(IncidenceMatrix* p)
{
    ptr = p;
    count = 1;
}
IncidenceMatrix* PointerIncid::operator -> ()
{
    count++;
    std::cout << "��������� ��������!";
    return ptr;
}
PointerIncid::~PointerIncid()
{
    if (ptr != nullptr) delete ptr;
}
int PointerIncid::get_count()
{
    return count;
}