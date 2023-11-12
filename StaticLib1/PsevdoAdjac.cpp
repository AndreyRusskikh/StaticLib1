#include "pch.h";
#include "PsevdoAdjac.h"
PsevdoAdjac::PsevdoAdjac(int** row, int numRowStart, int numRowEnd)
{
    _numRowStart = numRowStart;
    _numRowEnd = numRowEnd;
    int matSize = numRowEnd - numRowStart + 1;
    int a = 0;
    while (row[0][a] == 0 || row[0][a] == 1 || row[0][a] == -1)
    {
        a++;
    }
    matrixs = new int* [matSize];
    for (int i = 0; i < matSize; ++i)
    {
        matrixs[i] = new int[a];
    }
    for (int b = 0; b < matSize; b++)
    {
        for (size_t j = 0; j < a; j++)
        {
            matrixs[b][j] = row[b][j];
        }
    }

}

PsevdoAdjac::~PsevdoAdjac()
{
    if (matrixs == nullptr)
        return;

    for (int i = 0; i < _numRowStart; ++i)
    {
        delete[] matrixs[i];
    }

    delete[] matrixs;
    matrixs = nullptr;
}
