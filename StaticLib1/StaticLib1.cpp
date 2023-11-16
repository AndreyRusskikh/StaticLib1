
#include "pch.h"
#include "AdjacencyMatrix.h"
#include "framework.h"

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
		cout << "Размеры переданной или считываемой матрицы не совпадают с принимающей матрицой\n";
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
	if (adjac._numVertices <= 0 || adjac.matrix[0][0] == -1)
	{
		cout << "Матрица пуста\n";
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
PsevdoAdjac AdjacencyMatrix::operator()(int start, int count)
{
	PsevdoAdjac psevNull(matrix[start], 0, 0, _numVertices);

	if (_numVertices <= 0)
	{
		cout << "Матрица пуста\n";
		return psevNull;
	}

	if (start < 0 && start > _numVertices)
	{
		assert(start >= 0 && start < _numVertices);
		return psevNull;

	}
	if (count < 0 && count + start > _numVertices)
	{
		assert(count >= 0 && count + start < _numVertices);
		return psevNull;
	}
	PsevdoAdjac psev(matrix[start], start, count, _numVertices);
	
	return psev;
}


void AdjacencyMatrix::writeMatrixToFile(std::ofstream& ofs)
{
	ofs << *this;
}

void AdjacencyMatrix::readMatrixFromFile(std::ifstream& ifs)
{
	ifs >> *this;
}

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& other)
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

	return *this;

}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& other)
{

	_numVertices = other._numVertices;

	createMatrix(_numVertices);

	for (int i = 0; i < _numVertices; i++)
	{
		for (int j = 0; j < _numVertices; j++)
		{
			matrix[i][j] = other.matrix[i][j];
		}
	}

	std::cout << "\nКонструктор копирования сработал\n";

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
				matrix[i][j] = 0;
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
	if (matrix == nullptr || matrix[0][0] == -1)
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
	matrix = nullptr;
}


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

	std::cout << "\nКонструктор копирования сработал\n";

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

	if (this == &other)
		return *this;

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

IncidenceMatrix::IncidenceMatrix(const IncidenceMatrix& other)
{

	_numVertices = other._numVertices;
	_numEdges = other._numEdges;
	_count = other._count;

	createMatrix();

	for (int i = 0; i < _numVertices; i++)
	{
		for (int j = 0; j < _numEdges; j++)
		{
			matrix[i][j] = other.matrix[i][j];
		}
	}
	std::cout << "\nКонструктор копирования сработал\n";


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
		cout << "Размеры переданной или считываемой матрицы не совпадают с принимающей матрицой\n";
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
