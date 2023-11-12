#include "pch.h"
#include "PointerIncid.h"
#include "PointerAdjac.h"
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    setlocale(LC_ALL, "ukr");

    // Создаем матрицу смежности
    AdjacencyMatrix* adjac = new AdjacencyMatrix(10);
    AdjacencyMatrix* adjac2 = new AdjacencyMatrix(10);
    AdjacencyMatrix* adjac3 = new AdjacencyMatrix(10);

    // Создаем объекты-указатели на матрицу смежности
    PointerAdjac ptrAdjac(adjac);
    PointerAdjac ptrAdjac2(adjac2);
    PointerAdjac ptrAdjac3(adjac3);

    // Добавляем рёбра в матрицу смежности через указатель
    ptrAdjac->addDefault(10);
    ptrAdjac2->addDefault(10);

    // Создаем псевдо-рёбра
    PsevdoAdjac psevdAdjac(ptrAdjac->operator()(3, 6), 3, 6);
    PsevdoAdjac psevdAdjac2(ptrAdjac->operator()(0, 1, 10), 0, 1);
    

    // //Присваиваем матрице смежности значения псевдо-рёбер
    ptrAdjac->operator=(psevdAdjac);

    // //Добавляем значения псевдо-рёбер к матрице смежности
    ptrAdjac2->operator+=(psevdAdjac2);

     //Выводим матрицу смежности
    ptrAdjac->Show();
    ptrAdjac2->Show();

     //Освобождаем память
    //delete adjac;

    return 0;
}
