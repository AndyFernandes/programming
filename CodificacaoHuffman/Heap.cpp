#include <stdio.h>
#include "Heap.h"

void Heap::construir(int *vetor, int ptamanho){
    tamanho = ptamanho;
    //TODO check if the index is correct
    for(int *i = vetor; i != vetor + ptamanho; ++i){
        *heap = *i;
        ++heap;
        cout << *heap << endl;
    }

    // for(int index = (ptamanho)/2; index >= 0; --index){
    //     heapify(heap, index);
    //     cout << *(heap + index) << endl;
    // }
}

void Heap::heapify(int* vetor, int index){
    int *left = getLeft(index);
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
    // cout << *(vetor+largest) << endl;
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