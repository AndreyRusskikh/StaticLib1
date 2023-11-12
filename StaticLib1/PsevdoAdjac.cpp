#include "pch.h"
#include "PsevdoAdjac.h"
PsevdoAdjac::PsevdoAdjac(int** row, int numRowStart, int numRowEnd)
{
	_numRowStart = numRowStart;
	_numRowEnd = numRowEnd;
	matrixs = row;
}