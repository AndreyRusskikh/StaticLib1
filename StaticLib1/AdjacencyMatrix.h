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

    // Деструктор
    ~AdjacencyMatrix();

    int& operator[](const int index);

    AdjacencyMatrix& operator=(const AdjacencyMatrix& other);
    AdjacencyMatrix& operator=(const PsevdoAdjac& other);
    AdjacencyMatrix& operator+=(const PsevdoAdjac& other);
    
    AdjacencyMatrix(const AdjacencyMatrix& other);
    int** operator()(int row, int end);
    int** operator()(int row, int end, int numMatrix);

    // Додати ребро між вершинами from і to
    void addEdge(int from, int to);
    void addDefault(int n);
    void Show();
    // Видалити ребро між вершинами from і to
    void removeEdge(int from, int to);
    // Замінити значення ребра між вершинами from і to
    void replaceEdge(int from, int to, int value);
    // Отримати ребро між вершинами from і to
    int getEdge(int from, int to);

    void readMatrixFromFile(std::ifstream& is);

    // Метод для запису матриці у файл
    void writeMatrixToFile(std::ofstream& is);
    void shortestPathUsingAdjacencyMatrix(int source, int destination);

    friend std::istream& operator>>(std::istream& is, AdjacencyMatrix& adjac);
    friend std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& adjac);

private:
    int _numVertices;  // Розмір матриці
    int** matrix = new int* [_numVertices];  // Матриця суміжності

    // Створення матриці з нулів
    void createMatrix(int numVert);

    // Видалення матриці
    void deleteMatrix();
};
