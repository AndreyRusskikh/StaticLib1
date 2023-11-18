#include "pch.h"
#include "PseudoAdjac.h"


PsevdoAdjac::PsevdoAdjac(int* _ptr, int _numRowStart, int _countMat, int _countNumELMat)
	: ptr(_ptr), _numRowStart(_numRowStart), countMat(_countMat), countNumELMat(_countNumELMat)
{

}

PsevdoAdjac::~PsevdoAdjac()
{
	// delete ptr;
}

PsevdoAdjac& PsevdoAdjac::operator=(const AdjacencyMatrix& other)
{
    if (other._numVertices != countNumELMat || countMat <= 0 || _numRowStart < 0 || countMat + _numRowStart > other._numVertices)
    {
        cout << "Некорректные параметры для присваивания матрицы\n";
        return *this;
    }

    for (int i = _numRowStart; i < countMat +_numRowStart + 1; ++i)
    {
        for (int j = 0; j < countNumELMat && j < other._numVertices; ++j)
        {
            ptr[j] = other.matrix[i * countNumELMat + j];
        }
        ptr = ptr + countNumELMat;

    }

    return *this;
}
