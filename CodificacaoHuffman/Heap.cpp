#include <stdio.h>
#include "Heap.h"

No* newNo(char chave, int qnt, No* filhoEsquerdo, No* filhoDireito){
    No* no = (No*) malloc(sizeof(No));
    no->chave = chave;
    no->qnt = qnt;
    no->filhoEsquerdo = filhoEsquerdo;
    no->filhoDireito = filhoDireito;
    return no;
}

void Heap::construir(dict tabela){
    // heapSize = tabela.size();;

    // heap = (No**)malloc(heapSize * sizeof(No*));

    // int i = 0;
    // for(auto it = tabela.cbegin(); it != tabela.cend(); ++it){
    //     heap[i] = newNo(it->first , it->second, nullptr, nullptr);
    //     i++;
    // }

    // for(int index = (heapSize-1) / 2; index >=0; index--){
    //     heapify(heap, index);
    // }
    
    heapSize = tabela.size();
    // inicialização da heap
    heap = (No**) malloc(sizeof(No*) * heapSize);
    No** aux = (No**) malloc(sizeof(No*) * heapSize);
    int i = 0;
    // copia dos valores da tabela pro formato de uma heap
    for(par elemento: tabela){
        // Instanciando nó
        No* no = (No*) malloc(sizeof(No));
        no->chave = elemento.first;
        no->qnt = elemento.second;
        no->filhoEsquerdo = nullptr;
        no->filhoDireito = nullptr;
        aux[i] =  no;
        i++;
    }
    
    for(int index = (heapSize-1) / 2; index >=0; index--){
        heapify(aux, index);
    }
    heap = aux;
    for(int index = 0; index < heapSize; index++){
        cout << heap[index]->chave << " : " << heap[index]->qnt << " | ";
    }
}

void Heap::heapify(No** pVector, int pIndex){
    int left = getLeft(pIndex);
    int right = getRight(pIndex);
    int largest;
    
    if(left < heapSize && pVector[left]->qnt < pVector[pIndex]->qnt)
        largest = left;
    else
        largest = pIndex;
    
    if(right < heapSize && pVector[right]->qnt < pVector[largest]->qnt)
        largest = right;

    if(largest != pIndex){
        Swap(pVector, pIndex, largest);
        heapify(pVector, largest);
    }
}

int Heap::getParent(int pIndex){
    return (pIndex-1) / 2;
}

int Heap::getLeft(int pIndex){
    return 2 * pIndex;
}

int Heap::getRight(int pIndex){
    return 2*pIndex + 1;
}

void Heap::Swap(No** p, int pIndex, int largest){
    No* aux = p[pIndex];
    p[pIndex] = p[largest];
    p[largest] = aux;
}   

// ver questão do decremento
void Heap::insert(No* x){
    heapSize = heapSize + 1;
    int k = heapSize - 1;
    while(k > 1 && heap[getParent(k)]->qnt > x->qnt){
        heap[k] = heap[getParent(k)];
        k = getParent(k);
    }
    heap[k] = x;

    // printando sempre que eu insiro pra ver se tá ok
    // for(int index = 0; index < heapSize; index++){
    //     cout << heap[index]->chave << " : " << heap[index]->qnt << " | ";
    // }
}

No* Heap::minimum(){
    return heap[0];
}

No* Heap::extractMinimum(){
    if (heapSize < 1){
        cout << "Heap underflow";
        return nullptr;
    }
    // No* max = (No*) malloc(sizeof(No));
    // max->chave = heap[0].chave;
    // max->qnt = heap[0].qnt;
    // max->filhoEsquerdo = heap[0].filhoEsquerdo;
    // max->filhoDireito = heap[0].filhoDireito;
    No* max = heap[0];
    
    heap[0] = heap[heapSize-1];
    heapSize = heapSize - 1;
    heapify(heap, 0);
    return max;
}