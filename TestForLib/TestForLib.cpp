#include "pch.h"
#include "PointerIncid.h"
#include "PointerAdjac.h"
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ukr");


    AdjacencyMatrix* adjac = new AdjacencyMatrix(10);
    AdjacencyMatrix* adjac2 = new AdjacencyMatrix(10);
    AdjacencyMatrix* adjac3 = new AdjacencyMatrix(10);

    AdjacencyMatrix adjac4(10);
    AdjacencyMatrix adjac5(10);

    PointerAdjac ptrAdjac(adjac);
    PointerAdjac ptrAdjac2(adjac2);
    PointerAdjac ptrAdjac3(adjac3);


    ptrAdjac->addDefault(10);
    ptrAdjac->addEdge(0, 1);
    ptrAdjac->addEdge(1, 1);
    ptrAdjac->addEdge(3, 1);
    ptrAdjac->addEdge(4, 2);
    ptrAdjac->addEdge(5, 5);
    ptrAdjac->addEdge(8, 9);
    ptrAdjac->addEdge(3, 6);
    ptrAdjac->addEdge(2, 4);
    ptrAdjac->addEdge(3, 4);
    ptrAdjac->addEdge(3, 2);
    ptrAdjac->addEdge(2, 3);
    ptrAdjac->addEdge(9, 1);
    ptrAdjac->addEdge(8, 0);

    adjac4.addDefault(10);
     

    adjac5(2, 2) = adjac4;

    adjac5.Show();

    return 0;
}
