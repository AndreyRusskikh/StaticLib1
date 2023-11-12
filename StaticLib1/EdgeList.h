#pragma once
#include <fstream>
#include <iostream>
#include <cassert>


class EdgeList
{
public:
    // ����������� ��� ���������
    EdgeList();

    // ����������� � �����������
    EdgeList(int edges);
    // ����������
    ~EdgeList();

    // �������������� ��������� [] ��� ������� �� ������ ����� �������
    int& operator[](const int index);
    EdgeList& operator=(const EdgeList& other);
    EdgeList(const EdgeList& other);
    int& operator()(int row, int col);

    void readEdgeListFromFile(std::ifstream& is);

    // ����� ��� ������ ������� � ����
    void writeEdgeLisToFile(std::ofstream& os);
    void shortestPathUsingEdgeList(int source, int destination);

    // ������ �����
    void addEdge(int from, int to);

    void addDefault(int n);

    void Show();

    // �������� ����� �� ���� �������
    void removeEdge(int edgeNumber);

    // ������� �������� ����� �� ���� �������
    void replaceEdge(int edgeNumber, int from, int to);

    // �������� ����� �� ���� �������
    int* getEdge(int edgeNumber);

    friend std::istream& operator>>(std::istream& is, EdgeList& edgeList);

    friend std::ostream& operator<<(std::ostream& os, EdgeList& edgeList);


private:
    static const int _maxSize = 1000; // ������������ ����� ������ �����
    int _numEdges;  // ʳ������ �����
    int _count;
    int** edgeArray = new int* [_numEdges]; // ����� �����
    bool isEmpty;

    // ��������� ������ �����
    void createEdgeArray();

    // ��������� ������ �����
    void deleteEdgeArray();
};