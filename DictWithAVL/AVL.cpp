#include <stdio.h>
#include "Heap.h"

bool No::isEmpty(){
    if(root == nullptr) return true;
    else return false;
}

void AVL::rotationLeft(No no){

}

void AVL::rotationRight(No no){

}

bool AVL::inserir(int chave, int value){

}

int AVL::search(int chave, No no){
    if(chave == null && no.isEmpty())
        return -1;

    if(no.chave == chave && no.isEmpty())
        return no;
    else if(no.chave > chave)
        return search(chave, no.filhoEsquerdo);
    else
        return search(chave, no.filhoDireito);
}

bool AVL::remove(int chave){

}

void preOrder(No no){
    if(no.isEmpty()) return;
    cout << no.chave << " ";
    preOrder(no.filhoEsquerdo);
    preOrder(no.filhoDireito);
}