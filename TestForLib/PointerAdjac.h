#pragma once
#include <AdjacencyMatrix.h>
class PointerAdjac:
    public AdjacencyMatrix
{
    AdjacencyMatrix* ptr;
    int count;
public:
    PointerAdjac(AdjacencyMatrix* p);

    AdjacencyMatrix* operator -> ();

    ~PointerAdjac();
    int get_count();
};

