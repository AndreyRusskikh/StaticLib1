#pragma once
class AdjacencyMatrix;
class PsevdoAdjac
{

public:
    PsevdoAdjac(int*& _ptr, int _numRowStart, int _countMat, int _countNumELMat);
    ~PsevdoAdjac();

    PsevdoAdjac& operator=(const AdjacencyMatrix& other);

    int _numRowStart;
    int countMat;
    int countNumELMat;
    int*& ptr;

};
