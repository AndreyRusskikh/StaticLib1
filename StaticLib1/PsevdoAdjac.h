#pragma once
class PsevdoAdjac
{
public:
	PsevdoAdjac(int** row, int numRowStart, int numRowEnd)
	{
		_numRowStart = numRowStart;
		_numRowEnd = numRowEnd;
		matrixs = row;
	}
	int _numRowStart;
	int _numRowEnd;
	int** matrixs = new int*[_numRowStart];
};

