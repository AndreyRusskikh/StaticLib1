#pragma once
class PsevdoAdjac
{
public:
    PsevdoAdjac(int** row, int numRowStart, int numRowEnd);
    ~PsevdoAdjac();
    int _numRowStart;
    int _numRowEnd;
    int** matrixs;
};
