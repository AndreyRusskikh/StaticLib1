#pragma once
#include "IncidenceMatrix.h";
class PointerIncid :
    public IncidenceMatrix
{
    IncidenceMatrix* ptr;
    int count;
public:
    PointerIncid(IncidenceMatrix* p);

    IncidenceMatrix* operator -> ();

    ~PointerIncid();
    int get_count();
};

