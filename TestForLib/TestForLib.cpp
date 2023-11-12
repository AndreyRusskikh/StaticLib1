#include "pch.h";
#include "PointerIncid.h";
#include "PointerAdjac.h";
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	setlocale(LC_ALL, "ukr");

	AdjacencyMatrix adjac = new AdjacencyMatrix(10);
	PointerAdjac ptrAdjac(adjac);

	ptrAdjac->addDefault(10);
	cout << ptrAdjac(5, 3) << "\n";
	cout << ptrAdjac(0, 0) << "\n";
	cout << ptrAdjac(2, 7) << "\n";

	return 0;
}

