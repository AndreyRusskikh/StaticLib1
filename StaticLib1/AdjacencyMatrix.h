#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class PsevdoAdjac;

class AdjacencyMatrix
{
public:

    AdjacencyMatrix();

    AdjacencyMatrix(int n);

    // ����������
    ~AdjacencyMatrix();

    int& operator[](const int index);

    AdjacencyMatrix& operator=(const AdjacencyMatrix& other);
   
    
    AdjacencyMatrix(const AdjacencyMatrix& other);
    PsevdoAdjac operator()(int row, int end);


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

    int _numVertices;
    int* matrix;  // ���������� ������ ��� ������� ���������

    // ��������� ������� � ����
    void createMatrix(int numVert);

    // ��������� �������
    void deleteMatrix();
   
};
