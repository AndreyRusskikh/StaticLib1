#pragma once
#include <fstream>
#include <iostream>
#include <cassert>


class EdgeList
{
public:
    // Конструктор без параметрів
    EdgeList();

    // Конструктор з параметрами
    EdgeList(int edges);
    // Деструктор
    ~EdgeList();

    // Перевантаження оператора [] для доступу до списку ребер підграфа
    int& operator[](const int index);
    EdgeList& operator=(const EdgeList& other);
    EdgeList(const EdgeList& other);
    int& operator()(int row, int col);

    void readEdgeListFromFile(std::ifstream& is);

    // Метод для запису матриці у файл
    void writeEdgeLisToFile(std::ofstream& os);
    void shortestPathUsingEdgeList(int source, int destination);

    // Додати ребро
    void addEdge(int from, int to);

    void addDefault(int n);

    void Show();

    // Видалити ребро за його номером
    void removeEdge(int edgeNumber);

    // Замінити значення ребра за його номером
    void replaceEdge(int edgeNumber, int from, int to);

    // Отримати ребро за його номером
    int* getEdge(int edgeNumber);

    friend std::istream& operator>>(std::istream& is, EdgeList& edgeList);

    friend std::ostream& operator<<(std::ostream& os, EdgeList& edgeList);


private:
    static const int _maxSize = 1000; // Максимальний розмір списку ребер
    int _numEdges;  // Кількість ребер
    int _count;
    int** edgeArray = new int* [_numEdges]; // Масив ребер
    bool isEmpty;

    // Створення масиву ребер
    void createEdgeArray();

    // Видалення масиву ребер
    void deleteEdgeArray();
};