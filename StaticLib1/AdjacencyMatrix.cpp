#include "pch.h"

AdjacencyMatrix::AdjacencyMatrix()
{
    _numVertices = 0;
    matrix = nullptr;
}

// Конструктор з параметрами
AdjacencyMatrix::AdjacencyMatrix(int n)
{
    _numVertices = n;
    matrix = new int* [_numVertices];
    createMatrix(_numVertices);
}

// Деструктор
AdjacencyMatrix::~AdjacencyMatrix()
{
    deleteMatrix();
}
void AdjacencyMatrix::shortestPathUsingAdjacencyMatrix(int source, int destination)
{
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

        for (int v = 0; v < _numVertices; ++v)
        {
            if (!visited[v] && matrix[u][v] && distance[u] != INT_MAX &&
                distance[u] + matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + matrix[u][v];
                parent[v] = u;
            }
        }
    }

    if (parent[destination] == -1) {
        std::cerr << "There is no path from vertex " << source << " to vertex " << destination << "." << std::endl;
    }
    else
    {
        std::cout << "Shortest path from vertex " << source << " to vertex " << destination << ":\n";
        int currentVertex = destination;
        int* path = new int[_numVertices];
        int pathLength = 0;

        while (currentVertex != -1)
        {
            path[pathLength++] = currentVertex;
            currentVertex = parent[currentVertex];
        }

        for (int i = pathLength - 1; i >= 0; --i)
        {
            std::cout << path[i];
            if (i > 0)
            {
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


int& AdjacencyMatrix::operator[](const int index)
{
    if (index < 0 && index > _numVertices)
    {
        static int one = -1;
        return one;
    }
    else
    {
        int first, second;
        first = index / _numVertices;
        second = index - (first * _numVertices);
        return matrix[first][second];
    }
}
std::istream& operator>>(std::istream& is, AdjacencyMatrix& adjac)
{
    int numVerFromFile;

    is >> numVerFromFile;
    //adjac.createMatrix(adjac._numVertices);

    if (numVerFromFile != adjac._numVertices)
    {
        cout << "Матрица из файла не совпадает с переданной матрицей" << "\n";
        return is;
    }
    else
    {
        for (int i = 0; i < adjac._numVertices; ++i)
        {
            for (int j = 0; j < adjac._numVertices; ++j)
            {
                is >> adjac.matrix[i][j];
            }
        }
    }
    if (adjac.matrix[0][0] == -1)
    {
        adjac.matrix[0][0] = 0;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& adjac)
{
    if (adjac.matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return os;
    }
    os << adjac._numVertices << "\n";

    for (int i = 0; i < adjac._numVertices; i++)
    {
        for (int j = 0; j < adjac._numVertices; j++)
        {
            os << adjac.matrix[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}
int& AdjacencyMatrix::operator()(int row, int col)
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
void AdjacencyMatrix::writeMatrixToFile(std::ofstream& ofs)
{
    ofs << *this;
}

void AdjacencyMatrix::readMatrixFromFile(std::ifstream& ifs)
{
    ifs >> *this;
}

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix other)
{
    if (this == &other)
        return *this;

    _numVertices = other._numVertices;
    deleteMatrix();
    createMatrix(_numVertices);
    for (int i = 0; i < _numVertices; i++)
    {
        for (int j = 0; j < _numVertices; j++)
        {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    if (matrix[0][0] == -1)
    {
        matrix[0][0] = 0;
    }
    return *this;

}
AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& other)
{

 /*   _numVertices = other._numVertices;

    createMatrix(_numVertices);

    for (int i = 0; i < _numVertices; i++)
    {
        for (int j = 0; j < _numVertices; j++)
        {
            matrix[i][j] = other.matrix[i][j];
        }
    }*/

    std::cout << "Сработал конструктор копирования\n";
}


void AdjacencyMatrix::createMatrix(int numVert)
{
    if (numVert < 0)
    {
        cout << "Количество вершин не может быть меньше 0\n";
        return;
    }
    else
    {
        matrix = new int* [numVert];
        for (int i = 0; i < numVert; i++)
        {
            matrix[i] = new int[numVert];
            for (int j = 0; j < numVert; j++)
            {
                matrix[i][j] = -1;
            }
        }
    }

}



void AdjacencyMatrix::addEdge(int from, int to)
{

    if (from < 0 || from > _numVertices || to < 0 || to > _numVertices)
        return;
    else
    {
        matrix[from][to] = 1;
    }

    if (matrix[0][0] == -1)
    {
        matrix[0][0] = 0;
    }

}

void AdjacencyMatrix::addDefault(int n)
{
    if (n > 0 && n < _numVertices + 1)
    {
        for (int i = 0; i < n / 2; i++)
        {
            int from = n / 2 - i;
            int to = n / 2 + i - 1;
            if (from >= 0 && from < _numVertices && to >= 0 && to < _numVertices)
            {
                addEdge(from, to);

            }
        }
    }
}
void AdjacencyMatrix::Show()
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    std::cout << "Number of Vertices: " << _numVertices << "\n";

    for (int i = 0; i < _numVertices; i++)
    {
        for (int j = 0; j < _numVertices; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void AdjacencyMatrix::removeEdge(int from, int to)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    if (from < 0 || from > _numVertices || to < 0 || to > _numVertices)
        return;

    else
    {
        matrix[from][to] = 0;
    }
}

void AdjacencyMatrix::replaceEdge(int from, int to, int value)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return;
    }
    if (from < 0 || from > _numVertices || to < 0 || to > _numVertices)
        return;

    else
    {
        matrix[from][to] = value;
    }
}

int AdjacencyMatrix::getEdge(int from, int to)
{
    if (matrix[0][0] == -1)
    {
        std::cout << "Матрица пуста" << "\n";
        return matrix[0][0];
    }
    if (from < 0 || from > _numVertices || to < 0 || to > _numVertices)
        return 0;

    else
    {
        return matrix[from][to];
    }
}


// Видалення матриці
void AdjacencyMatrix::deleteMatrix()
{
    if (matrix == nullptr)
        return;

    for (int i = 0; i < _numVertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

