#include <stdio.h>
using namespace std;

class Heap {
    int *heap;
    int tamanho;  
    
    Heap(int *vetor, int ptamanho);

    void heapify(int* vetor, int index);

    int* getParent(int index);

    int* getLeft(int index);

    int* getRight(int index);

    void swap(int *p, int *p_);
};