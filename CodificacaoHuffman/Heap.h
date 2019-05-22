#include <stdio.h>
using namespace std;

class Heap {
    public:

    int heapSize;
    int* heap;

    void construir(int *pVector, int pSize);
    void heapify(int* pVector, int pIndex);

    int getParent(int pIndex);

    int getLeft(int pIndex);

    int getRight(int pIndex);

    void insert(int x);

    int minimum();

    int extractMinimum();

    void Swap(int *p, int pIndex, int largest);
};


