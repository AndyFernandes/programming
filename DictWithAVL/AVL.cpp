#include <stdio.h>
#include "AVL.hpp"

// Inicializa D como uma árvore vazia.
void inicializar (DicAVL &D){
    D.raiz = nullptr;
} 

int height(Noh *no){
    if(no == nullptr) return 0;
    return no->h;
}

int max(int a, int b){
    return (a > b)? a : b;
}

Noh* rotationLeft(Noh *x){
    Noh* paiX = x->pai;
    Noh* y = x->dir;
    Noh* filhoEsqY = y->esq;

     // Ponteiro de PaiX -> muda filho do lugar de X pra Y 
    if(paiX != nullptr){
        if(paiX->esq == x) paiX->esq = y;
        else if(paiX->dir == x) paiX->dir = y;
    }

     // X -> muda pai e muda filho direito
    x->pai = y;
    x->dir = filhoEsqY;

    // Y -> muda pai e muda filho esquerdo
    y->pai = paiX;
    y->esq = x; 
    
    // Filho direito de Y -> muda pai
    filhoEsqY->pai = x;

    //Atualizando alturas
    y->h = max(height(y->esq), height(y->dir)) + 1;
    x->h = max(height(x->esq), height(x->dir)) + 1;

    return y; 
}

Noh* rotationRight(Noh *y){
    Noh* paiY = y->pai;
    Noh* x = y->esq;
    Noh* filhoDirX = x->dir;

    // Ponteiro de PaiY -> muda filho do lugar de Y 
    if(paiY != nullptr){ // Atualizando ponteiro do filho do pai de Y para no lugar de y ser x
        if(paiY->esq == y) paiY->esq = x;
        else if(paiY->dir == y) paiY->dir = x;
    }

    // X -> muda pai e muda filho direito
    x->pai = paiY;
    x->dir = y; // Y é agora filho direito de y

    // Y -> muda pai e muda filho esquerdo
    y->pai = x; // X agora é o pai de y
    y->esq = filhoDirX; // Filho Direito de X agora vira filho Esquerdo de Y
    
    // Filho direito de Y -> muda pai
    filhoDirX->pai = y;

    //Atualizando alturas
    y->h = max(height(y->esq), height(y->dir)) + 1;
    x->h = max(height(x->esq), height(x->dir)) + 1;
    
    return x;
}

// Retorna um ponteiro para o nó da chave procurada, ou nulo se a chave não estiver em D.
Noh* procurar(DicAVL &D, TC c){
    Noh* no = D.raiz;

    while(no != nullptr){
        TC chave = no->chave;
        if(chave == c) return no;
        else if(chave > c) no = no->esq;
        else if(chave < c) no = no->dir;
    }
    return nullptr;
}

bool isLeaf(Noh* no){
    if(no->esq == nullptr && no->dir == nullptr) return true;
    return false;
}

// Retorna um ponteiro para o novo nó ou nulo se erro de alocação
Noh* inserir (DicAVL &D, TC c, TV v){

} 

// n aponta para o nó a ser removido
void remover (DicAVL &D, Noh *n){

} 

// Desaloca os nós da árvore.
void terminar (DicAVL &D){
    // acessar a raiz do dicionario e visitar em pré-ordem desalocando os nós
    Noh* no = D.raiz;

    while(no != nullptr){
        if(isLeaf(no)) free(no);
        else if(chave > c) no = no->esq;
        else if(chave < c) no = no->dir;
    }
} 