#pragma once
#include <fstream>
#include <iostream>
#include <cassert>


class IncidenceMatrix
{
public:

    // Конструктор без параметрів
    IncidenceMatrix();

    // Конструктор з параметрами
    IncidenceMatrix(int vertices, int edges);
    // Деструктор
    ~IncidenceMatrix();
    int& operator[](const int index);
    IncidenceMatrix& operator=(const IncidenceMatrix& other);
    IncidenceMatrix(const IncidenceMatrix& other);
    int& operator()(int row, int col);

    void readMatrixFromFile(std::ifstream& is);
    // Метод для запису матриці у файл
    void writeMatrixToFile(std::ofstream& is);
    void shortestPathUsingIncidenceMatrix(int source, int destination);


    // Додати ребро між вершинами from і to
    void addEdge(int from, int to, bool& isEnd);

    void addDefault(int n);

    void Show();

    // Видалити ребро за його номером
    void removeEdge(int edgeNumber);

    // Замінити значення ребра за його номером
    void replaceEdge(int edgeNumber, int from, int to);

    // Отримати ребро за його номером
    int* getEdge(int edgeNumber);
    friend std::ostream& operator<<(std::ostream& os, const IncidenceMatrix& incid);

    friend std::istream& operator>>(std::istream& is, IncidenceMatrix& incid);
private:

    int _numVertices;  // Кількість вершин
    int _numEdges;     // Кількість ребер
    int _count;
    int** matrix = new int* [_numVertices];     // Матриця інцидентності

    // Створення матриці з нулів
    void createMatrix();

    // Видалення матриці
    void deleteMatrix();

};
