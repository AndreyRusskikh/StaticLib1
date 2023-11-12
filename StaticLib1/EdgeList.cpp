#include "pch.h"
#include "EdgeList.h"

EdgeList::EdgeList()
{
    _numEdges = 0;
    _count = 0;
    edgeArray = nullptr;
}

EdgeList::EdgeList(int edges)
{
    _numEdges = edges;
    _count = 0;
    createEdgeArray();
}

EdgeList::~EdgeList() {
    deleteEdgeArray();
}

int& EdgeList::operator[](const int index)
{
    if (index >= 0 && index < _numEdges)
    {
        return edgeArray[index][0];
    }
    else
        throw new _exception;
}
void EdgeList::shortestPathUsingEdgeList(int source, int destination)
{
    if (isEmpty)
    {
        std::cout << "Список пуст" << "\n";
        return;
    }
    int _numVertices = _numEdges * 2;

    if (source < 0 || source >= _numVertices || destination < 0 || destination >= _numVertices)
    {
        std::cerr << "Invalid source or destination vertex." << std::endl;
        return;
    }

    int* distance = new int[_numVertices];
    bool* visited = new bool[_numVertices];
    int* parent = new int[_numVertices];

    for (int i = 0; i < _numVertices; ++i) {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int i = 0; i < _numVertices - 1; ++i) {
        int minDistance = INT_MAX;
        int u = -1;

        for (int v = 0; v < _numVertices; ++v) {
            if (!visited[v] && distance[v] < minDistance) {
                minDistance = distance[v];
                u = v;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = true;

        for (int e = 0; e < _numEdges; ++e) {
            int from = edgeArray[e][0];
            int to = edgeArray[e][1];

            if ((from == u || to == u) && visited[from] != visited[to]) {
                int v = (from == u) ? to : from;

                if (visited[u] && distance[u] != INT_MAX && distance[u] + 1 < distance[v]) {
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

EdgeList& EdgeList::operator=(const EdgeList& other)
{
    if (this == &other)
        return *this;
    else
    {
        _numEdges = other._numEdges;
        _count = other._count;
        isEmpty = other.isEmpty;
        deleteEdgeArray();
        createEdgeArray();
        for (int i = 0; i < _numEdges; i++)
        {
            edgeArray[i][0] = other.edgeArray[i][0];
            edgeArray[i][1] = other.edgeArray[i][1];
            edgeArray[i][2] = other.edgeArray[i][2];
        }
    }

    return *this;
}
int& EdgeList::operator()(int source, int end)
{
    if (_numEdges <= 0)
    {
        std::cout << "Список ребер пуст\n";
        int ret = -1;
        return ret;
    }
    assert(end >= 0 && end < _numEdges * 2);
    assert(source >= 0 && source < _numEdges * 2);
    for (size_t i = 0; i < _numEdges; i++)
    {
        if (edgeArray[i][1] == source)
        {
            if (edgeArray[i][2] == end)
                return edgeArray[i][0];
        }
    }
    int ret = -1;
    return ret;
}
EdgeList::EdgeList(const EdgeList& other)
{
    if (this != &other)
    {
        _numEdges = other._numEdges;
        _count = other._count;
        isEmpty = other.isEmpty;
        deleteEdgeArray();
        createEdgeArray();
        for (int i = 0; i < _numEdges; i++)
        {
            edgeArray[i][0] = other.edgeArray[i][0];
            edgeArray[i][1] = other.edgeArray[i][1];
            edgeArray[i][2] = other.edgeArray[i][2];
        }
    }
}

std::istream& operator>>(std::istream& is, EdgeList& edgeList)
{

    int numEdgeFromFile;
    is >> numEdgeFromFile;

    if (numEdgeFromFile != edgeList._numEdges)
    {
        std::cout << "Список ребер из файла не совпадает с переданным";
        return is;
    }


    for (int i = 0; i < edgeList._numEdges; i++)
    {
        for (int j = 0; j < 3; j++) { // 3 колонки (номер ребра, початок та кінець)
            is >> edgeList.edgeArray[i][j];
        }
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, EdgeList& edgeList)
{
    if (edgeList.isEmpty)
    {
        std::cout << "Список пуст" << "\n";
        return os;
    }
    os << edgeList._numEdges << "\n";


    for (int i = 0; i < edgeList._numEdges; i++)
    {
        for (int j = 0; j < 3; j++) { // 3 колонки (номер ребра, початок та кінець)
            os << edgeList.edgeArray[i][j] << ' ';
        }
        os << '\n'; // Перехід на наступний рядок
    }
    return os;
}

void EdgeList::readEdgeListFromFile(std::ifstream& is)
{
    is >> _numEdges;

    for (int i = 0; i < _numEdges; i++)
    {
        for (int j = 0; j < 3; j++) { // 3 колонки (номер ребра, початок та кінець)
            is >> edgeArray[i][j];
        }
    }
}

void EdgeList::writeEdgeLisToFile(std::ofstream& os)
{
    os << "Number of Edges: " << _numEdges << "\n";
    os << "Array of Edges: " << edgeArray << "\n";

    for (int i = 0; i < _numEdges; i++)
    {
        for (int j = 0; j < 3; j++) { // 3 колонки (номер ребра, початок та кінець)
            os << edgeArray[i][j] << ' ';
        }
        os << '\n'; // Перехід на наступний рядок
    }
}

void EdgeList::addEdge(int from, int to)
{
    isEmpty = false;

    if (_count < _numEdges)
    {
        edgeArray[_count][0] = _count + 1; // Номер ребра
        edgeArray[_count][1] = from;
        edgeArray[_count][2] = to;
        _count++;
    }
}

void EdgeList::addDefault(int n)
{
    isEmpty = false;
    for (int i = 0; i < n; i++)
    {
        this->addEdge(n / 2 + 1 - i, n / 2 + i);
    }
}

void EdgeList::Show()
{
    if (isEmpty)
    {
        std::cout << "Список пуст" << "\n";
        return;
    }
    for (int i = 0; i < _numEdges; i++)
    {
        for (int j = 0; j < 3; j++) { // 3 колонки (номер ребра, початок та кінець)
            std::cout << edgeArray[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void EdgeList::removeEdge(int edgeNumber)
{
    if (isEmpty)
    {
        std::cout << "Список пуст" << "\n";
        return;
    }
    if (edgeNumber < 0 && edgeNumber > _numEdges)
        return;
    else
    {
        for (int i = edgeNumber; i < _numEdges - 1; i++)
        {
            edgeArray[i][0] = i + 1; // Оновлення номерів ребер
            edgeArray[i][1] = edgeArray[i + 1][1];
            edgeArray[i][2] = edgeArray[i + 1][2];
        }
    }
}

void EdgeList::replaceEdge(int edgeNumber, int from, int to)
{
    if (isEmpty)
    {
        std::cout << "Список пуст" << "\n";
        return;
    }
    if (edgeNumber < 0 && edgeNumber > _numEdges)
        return;
    else
    {
        edgeArray[edgeNumber][1] = from;
        edgeArray[edgeNumber][2] = to;
    }
}

int* EdgeList::getEdge(int edgeNumber)
{
    if (isEmpty)
    {
        std::cout << "Список пуст" << "\n";
        return nullptr;
    }
    if (edgeNumber < 0 && edgeNumber > _numEdges)
        return nullptr;
    else
    {
        int* edge = new int[2];
        edge[0] = edgeArray[edgeNumber][1];
        edge[1] = edgeArray[edgeNumber][2];
        return edge;
    }
}

void EdgeList::createEdgeArray()
{
    edgeArray = new int* [_maxSize];
    for (int i = 0; i < _maxSize; i++)
    {
        edgeArray[i] = new int[3]; // 3 колонки: номер ребра, початок та кінець
    }
}

void EdgeList::deleteEdgeArray()
{
    if (edgeArray == nullptr)
        return;

    for (int i = 0; i < _maxSize; i++)
    {
        delete[] edgeArray[i];
    }
    delete[] edgeArray;

}
