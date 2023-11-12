#pragma once
class PsevdoAdjac
{
public:
	PsevdoAdjac(int** row, int numRowStart, int numRowEnd);
	int _numRowStart;
	int _numRowEnd;
	int** matrixs = new int*[_numRowStart];
};

