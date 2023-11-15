#include "pch.h"
#include "PsevdoAdjac.h"
#include <iostream>

PsevdoAdjac::PsevdoAdjac(int*& _ptr, int _numRowStart, int _countMat, int _countNumELMat)
	: ptr(_ptr), _numRowStart(_numRowStart), countMat(_countMat), countNumELMat(_countNumELMat)
{

}

PsevdoAdjac::~PsevdoAdjac()
{

}

PsevdoAdjac& PsevdoAdjac::operator=(const AdjacencyMatrix& other)
{
	if (other._numVertices != countNumELMat)
	{
		std::cout << "������� ���������� ��� ����������� ������� �� ��������� � ����������� ��������\n";
		return *this;
	}

	for (int i = _numRowStart; i < countMat; i++)
	{
		for (int j = 0; j < countNumELMat; j++)
		{
			ptr[j] = other.matrix[i][j];
		}
	}

	return *this;
}
