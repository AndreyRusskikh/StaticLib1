#pragma once
#include <fstream>
#include <iostream>
#include <cmath>;
#include <istream>
#include <sstream>
#include <cassert>
#include "PsevdoAdjac.h";
using namespace std;

class AdjacencyMatrix
{
public:

    AdjacencyMatrix();

    AdjacencyMatrix(int n);

    // ����������
    ~AdjacencyMatrix();

    int& operator[](const int index);

    AdjacencyMatrix& operator=(const AdjacencyMatrix& other);
    AdjacencyMatrix& operator=(const PsevdoAdjac& other);
    AdjacencyMatrix& operator+=(const PsevdoAdjac& other);
    
    AdjacencyMatrix(const AdjacencyMatrix& other);
    int** operator()(int row, int end);
    int** operator()(int row, int end, int numMatrix);

    // ������ ����� �� ��������� from � to
    void addEdge(int from, int to);
    void addDefault(int n);
    void Show();
    // �������� ����� �� ��������� from � to
    void removeEdge(int from, int to);
    // ������� �������� ����� �� ��������� from � to
    void replaceEdge(int from, int to, int value);
    // �������� ����� �� ��������� from � to
    int getEdge(int from, int to);

    void readMatrixFromFile(std::ifstream& is);

    // ����� ��� ������ ������� � ����
    void writeMatrixToFile(std::ofstream& is);
    void shortestPathUsingAdjacencyMatrix(int source, int destination);

    friend std::istream& operator>>(std::istream& is, AdjacencyMatrix& adjac);
    friend std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& adjac);

private:
    int _numVertices;  // ����� �������
    int** matrix = new int* [_numVertices];  // ������� ��������

    // ��������� ������� � ����
    void createMatrix(int numVert);

    // ��������� �������
    void deleteMatrix();
};
