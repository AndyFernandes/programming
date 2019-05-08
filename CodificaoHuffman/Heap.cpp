#include <stdio.h>
#include "Heap.h"

Heap::Heap(int *vetor, int ptamanho){
    tamanho = ptamanho;
    //TODO check if the index is correct
    for(int index = (tamanho-1)/2; index <=0; --index)
        heapify(vetor, index);
    *heap = *vetor;
}

void Heap::heapify(int* vetor, int index){
    int  *left = getLeft(index);
    int *right = getRight(index);
    int largest;
        
    if(*left <= tamanho && *left > *(vetor + index))
        largest = *left;
    else
        largest = index;

    if(*right <= tamanho && *right > *(vetor + largest))
        largest = *right;
    
    if(largest != index){
        swap(vetor+index, vetor+largest);
        heapify(vetor, largest);
    }
}

int* Heap::getParent(int index){
    return heap + index/2;
}

int* Heap::getLeft(int index){
    return heap + (2*index);
}

int* Heap::getRight(int index){
    return heap + ((2*index) + 1);
}

void Heap::swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}    