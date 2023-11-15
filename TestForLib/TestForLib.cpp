#include "pch.h"
#include "PointerIncid.h"
#include "PointerAdjac.h"
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    setlocale(LC_ALL, "ukr");


    AdjacencyMatrix* adjac = new AdjacencyMatrix(10);
    AdjacencyMatrix* adjac2 = new AdjacencyMatrix(10);
    AdjacencyMatrix* adjac3 = new AdjacencyMatrix(10);


    PointerAdjac ptrAdjac(adjac);
    PointerAdjac ptrAdjac2(adjac2);
    PointerAdjac ptrAdjac3(adjac3);


    ptrAdjac->addDefault(10);
    ptrAdjac2->addDefault(10);

    PsevdoAdjac psevdAdjac(ptrAdjac->operator()(3, 6), 3, 6);
    PsevdoAdjac psevdAdjac2(ptrAdjac->operator()(0, 1, 10), 0, 1);
    
    ptrAdjac->operator=(psevdAdjac);

    ptrAdjac2->operator+=(psevdAdjac2);

    ptrAdjac->Show();
    ptrAdjac2->Show();


    return 0;
}
