#pragma once
#include <fstream>
#include <iostream>
#include <cassert>


class IncidenceMatrix
{
public:

    // ����������� ��� ���������
    IncidenceMatrix();

    // ����������� � �����������
    IncidenceMatrix(int vertices, int edges);
    // ����������
    ~IncidenceMatrix();
    int& operator[](const int index);
    IncidenceMatrix& operator=(const IncidenceMatrix& other);
    IncidenceMatrix(const IncidenceMatrix& other);
    int& operator()(int row, int col);

    void readMatrixFromFile(std::ifstream& is);
    // ����� ��� ������ ������� � ����
    void writeMatrixToFile(std::ofstream& is);
    void shortestPathUsingIncidenceMatrix(int source, int destination);


    // ������ ����� �� ��������� from � to
    void addEdge(int from, int to, bool& isEnd);

    void addDefault(int n);

    void Show();

    // �������� ����� �� ���� �������
    void removeEdge(int edgeNumber);

    // ������� �������� ����� �� ���� �������
    void replaceEdge(int edgeNumber, int from, int to);

    // �������� ����� �� ���� �������
    int* getEdge(int edgeNumber);
    friend std::ostream& operator<<(std::ostream& os, const IncidenceMatrix& incid);

    friend std::istream& operator>>(std::istream& is, IncidenceMatrix& incid);
private:

    int _numVertices;  // ʳ������ ������
    int _numEdges;     // ʳ������ �����
    int _count;
    int** matrix = new int* [_numVertices];     // ������� ������������

    // ��������� ������� � ����
    void createMatrix();

    // ��������� �������
    void deleteMatrix();

};
