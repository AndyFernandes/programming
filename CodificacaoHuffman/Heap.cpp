#include <stdio.h>
#include "Heap.h"

void Heap::construir(int *pVector, int pSize){
    heapSize = pSize;
    heap = new int[pSize];

    //TODO check if the index is correct
    for(int index = (pSize-1) / 2; index >=0; index--){
        heapify(pVector, index);
    }
    heap = pVector;
}

void Heap::heapify(int* pVector, int pIndex){
    int left = getLeft(pIndex );
    int right = getRight(pIndex);
    int largest;
    
    if(left <= heapSize && pVector[left] < pVector[pIndex])
        largest = left;

    else
        largest = pIndex;
    

    if(right <= heapSize && pVector[right] < pVector[largest])
        largest = right;

    if(largest != pIndex){
        Swap(pVector, pIndex, largest);
        heapify(pVector, largest);
    }
}

int Heap::getParent(int pIndex){
    return pIndex / 2;
}

int Heap::getLeft(int pIndex){
    return 2 * pIndex;
}

int Heap::getRight(int pIndex){
    return 2*pIndex + 1;
}

void Heap::Swap(int *p, int pIndex, int largest){
    int aux;
    aux = p[pIndex];
    p[pIndex] = p[largest];
    p[largest] = aux;
}   