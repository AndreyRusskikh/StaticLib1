#include "pch.h"
#include "IncidenceMatrix.h"
using namespace std;
IncidenceMatrix::IncidenceMatrix()
{
    _numVertices = 0;
    _numEdges = 0;
    _count = 0;
    matrix = nullptr;
}

// Конструктор з параметрами
IncidenceMatrix::IncidenceMatrix(int vertices, int edges)
{
    _numVertices = vertices;
    _numEdges = edges;
    _count = 0;
    createMatrix();
}

// Деструктор
IncidenceMatrix::~IncidenceMatrix()
{
    deleteMatrix();
}

int& IncidenceMatrix::operator[](const int index)
{
    if (index < 0 || index > _numVertices * _numEdges)
    {
        int one = -1;
        return one;
    }
    else
    {
        int first, second;
        first = index / _numEdges;
        second = index - (first * _numEdges);
        return matrix[first][second];

    }
}
int& IncidenceMatrix::operator()(int row, int col)
{
    if (_numVertices <= 0)
    {
        cout << "Матрица пуста\n";
        int ret = -1;
        return ret;
    }
    assert(col >= 0 && col < _numVertices);
    assert(row >= 0 && row < _numVertices);

    return matrix[row][col];
}
IncidenceMatrix& IncidenceMatrix::operator=(const IncidenceMatrix& other)
{
    if (this != &other) {
        _numEdges = other._numEdges;
        _numVertices = other._numVertices;
        _count = other._count;
        deleteMatrix();
        createMatrix();
        for (int i = 0; i < _numVertices; i++)
        {
            for (int j = 0; j < _numEdges; j++)
            {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
    return *this;
}
IncidenceMatrix::IncidenceMatrix(const IncidenceMatrix& other)
{
    if (this != &other)
    {
        // Копируем количество вершин, рёбер и счётчик
        _numVertices = other._numVertices;
        _numEdges = other._numEdges;
        _count = other._count;

        // Выделяем память для матрицы
        createMatrix();

        // Копируем значения матрицы
        for (int i = 0; i < _numVertices; i++)
        {
            for (int j = 0; j < _numEdges; j++)
            {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const IncidenceMatrix& incid)
{
    if (incid.matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return os;
    }
    os << incid._numVertices << '\n';
    for (int i = 0; i < incid._numVertices; i++)
    {
        for (int j = 0; j < incid._numEdges; j++)
        {
            os << incid.matrix[i][j] << " ";
        }
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, IncidenceMatrix& incid)
{
    int numVerFromFile;

    is >> numVerFromFile;
    if (numVerFromFile != incid._numVertices)
    {
        cout << "Матрица из файла не совпадает с переданной матрицей";
        return is;
    }
    else
    {
        for (int i = 0; i < incid._numVertices; i++)
        {
            for (int j = 0; j < incid._numEdges; j++)
            {
                is >> incid.matrix[i][j];
            }
        }
    }
    if (incid.matrix[0][0] == -1)
    {
        incid.matrix[0][0] = 0;
    }
    return is;
}


void IncidenceMatrix::readMatrixFromFile(std::ifstream& is)
{
    is >> _numVertices;
    is >> _numEdges;

    for (int i = 0; i < _numVertices; i++)
    {
        for (int j = 0; j < _numEdges; j++)
        {
            is >> matrix[i][j];
        }
    }
}

// Метод для запису матриці у файл
void IncidenceMatrix::writeMatrixToFile(std::ofstream& os)
{
    os << "Number of Vertices: " << _numVertices << "\n";
    os << "Number of Edges: " << _numEdges << "\n";

    for (int i = 0; i < _numVertices; i++)
    {
        for (int j = 0; j < _numEdges; j++)
        {
            os << matrix[i][j] << ' ';
        }
        os << '\n'; // Перехід на наступний рядок
    }
}
void IncidenceMatrix::shortestPathUsingIncidenceMatrix(int source, int destination)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    if (source < 0 || source >= _numVertices || destination < 0 || destination >= _numVertices)
    {
        std::cerr << "Invalid source or destination vertex." << std::endl;
        return;
    }

    int* distance = new int[_numVertices];
    bool* visited = new bool[_numVertices];
    int* parent = new int[_numVertices];

    for (int i = 0; i < _numVertices; ++i)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int i = 0; i < _numVertices - 1; ++i)
    {
        int minDistance = INT_MAX;
        int u = -1;

        for (int v = 0; v < _numVertices; ++v)
        {
            if (!visited[v] && distance[v] < minDistance)
            {
                minDistance = distance[v];
                u = v;
            }
        }

        if (u == -1)
        {
            break;
        }

        visited[u] = true;

        for (int e = 0; e < _numVertices; ++e)
        {
            if (!visited[u] && matrix[u][e] == 1)
            {
                int v = -1;

                for (int j = 0; j < _numVertices; ++j)
                {
                    if (matrix[j][e] == -1)
                    {
                        v = j;
                        break;
                    }
                }

                if (v != -1 && distance[u] != INT_MAX && distance[u] + 1 < distance[v])
                {
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                }
            }
        }
    }

    if (parent[destination] == -1) {
        std::cerr << "There is no path from vertex " << source << " to vertex " << destination << "." << std::endl;
    }
    else {
        std::cout << "Shortest path from vertex " << source << " to vertex " << destination << ":\n";
        int currentVertex = destination;
        int* path = new int[_numVertices];
        int pathLength = 0;

        while (currentVertex != -1) {
            path[pathLength++] = currentVertex;
            currentVertex = parent[currentVertex];
        }

        for (int i = pathLength - 1; i >= 0; --i) {
            std::cout << path[i];
            if (i > 0) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;

        delete[] path;
    }

    delete[] distance;
    delete[] visited;
    delete[] parent;
}

// Додати ребро між вершинами from і to
void IncidenceMatrix::addEdge(int from, int to, bool& isEnd)
{

    if (_count < _numEdges)
    {
        if (from >= 0 && from < _numVertices && to >= 0 && to < _numVertices)
        {
            for (int edge = 0; edge < _numEdges; edge++)
            {
                bool edgeIsFree = true;
                for (int vertex = 0; vertex < _numVertices; vertex++)
                {
                    if (matrix[vertex][edge] != 0)
                    {
                        edgeIsFree = false;
                        break;
                    }
                }

                if (edgeIsFree)
                {
                    matrix[from][edge] = 1;
                    matrix[to][edge] = 1;
                    _count++;
                    return;
                }
            }
            // Если все ребра заняты создаем новое
            matrix[from][_count] = 1;
            matrix[to][_count] = 1;
            _count++;




        }
    }
    else
    {
        isEnd = true;
        return;
    }
    if (matrix[0][0] == -1)
    {
        matrix[0][0] = 0;
    }

}


void IncidenceMatrix::addDefault(int n)
{
    bool isItEnd = false;

    for (int i = 0; i < n; i++)
    {
        this->addEdge(n / 2 + 1 - i, n / 2 + i, isItEnd);
        if (isItEnd)
            return;
    }
}

void IncidenceMatrix::Show()
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    for (int i = 0; i < _numVertices; i++)
    {
        for (int j = 0; j < _numEdges; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// Видалити ребро за його номером
void IncidenceMatrix::removeEdge(int edgeNumber)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    if (edgeNumber < 0 || edgeNumber > _numEdges)
        return;
    else
    {
        for (int i = 0; i < _numVertices; i++)
        {
            matrix[i][edgeNumber] = 0;
        }
    }
}

// Замінити значення ребра за його номером
void IncidenceMatrix::replaceEdge(int edgeNumber, int from, int to)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    removeEdge(edgeNumber);
    if (edgeNumber < 0 || edgeNumber > _numEdges || from >= 0 || from < _numVertices || to >= 0 || to < _numVertices)
        return;
    else
    {
        matrix[from][edgeNumber] = 1;
        matrix[to][edgeNumber] = 1;
    }
}

// Отримати ребро за його номером
int* IncidenceMatrix::getEdge(int edgeNumber)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return nullptr;
    }
    if (edgeNumber < 0 || edgeNumber > _numEdges)
        return nullptr;
    else
    {
        int* edge = new int[_numVertices];
        for (int i = 0; i < _numVertices; i++)
        {
            edge[i] = matrix[i][edgeNumber];
        }
        return edge;
    }
}

void IncidenceMatrix::createMatrix()
{
    matrix = new int* [_numVertices];
    for (int i = 0; i < _numVertices; i++)
    {
        matrix[i] = new int[_numEdges];
        for (int j = 0; j < _numEdges; j++)
        {
            matrix[i][j] = -1;
        }
    }
}

// Видалення матриці
void IncidenceMatrix::deleteMatrix()
{
    if (matrix == nullptr)
        return;

    for (int i = 0; i < _numVertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

