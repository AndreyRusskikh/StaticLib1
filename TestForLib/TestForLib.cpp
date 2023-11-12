#include "pch.h";
#include "PointerIncid.h";
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	setlocale(LC_ALL, "ukr");

	cout << "Пункт 1, 2, 3\n";
	AdjacencyMatrix adjac1(10);
	adjac1.addDefault(10);
	AdjacencyMatrix adjac2(10);
	AdjacencyMatrix adjac3(10);
	adjac2 = adjac1;
	AdjacencyMatrix adjac6(adjac1);

	adjac6.Show();

	IncidenceMatrix incid(10, 5);
	IncidenceMatrix incid2(3, 5);
	cout << incid[2];

	EdgeList edgeList(20);
	edgeList.addDefault(20);
	EdgeList edgeList2(20);

	cout << "\nПункт 4\n";

	std::ofstream outputFile("output.txt");

	outputFile << edgeList;

	outputFile.close();

	std::ifstream inputFile("output.txt");
	inputFile >> edgeList2;

	edgeList2.Show();
	cout << "\n\nВведите количество элементов матрицы инцендентности, а затем элементы\n";


	cin >> incid2;
	cout << incid2;


	cout << "\nПункт 5\n";

	adjac3.addEdge(2, 5);
	adjac3.addEdge(5, 7);
	adjac3.addEdge(7, 3);
	adjac3.addEdge(3, 2);
	adjac3.addEdge(7, 8);
	adjac3.shortestPathUsingAdjacencyMatrix(2, 3);
	adjac3.shortestPathUsingAdjacencyMatrix(8, 2);

	cout << "\nПункт 6\n";


	AdjacencyMatrix adjac(10);
	adjac.addDefault(10);
	cout << adjac(5, 3) << "\n";
	cout << adjac(0, 0) << "\n";
	cout << adjac(2, 7) << "\n";

	EdgeList edlist(20);
	edlist.addDefault(20);
	cout << edlist(11, 10) << "\n";
	cout << edlist(15, 1) << "\n";
	cout << edlist(5, 16) << "\n";


	IncidenceMatrix incid3(20, 5);
	incid3.addDefault(20);
	cout << incid3(15, 1) << "\n";
	cout << incid3(0, 0) << "\n";
	cout << incid3(11, 0) << "\n";


	PointerIncid ptrIncid(new IncidenceMatrix);
	ptrIncid->addDefault(10);
	return 0;
}

