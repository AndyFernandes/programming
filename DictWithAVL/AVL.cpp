#include <iostream>
#include <stdio.h>
#include "AVL.hpp"
using namespace std;
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

bool isLeaf(Noh* no){
    if(no->esq == nullptr && no->dir == nullptr) return true;
    return false;
}

Noh* newNo(TC chave, TV value, Noh* pai, Noh* esq, Noh* dir, int h){
    Noh *no;
    no->chave = chave;
    no->valor = value;
    no->pai = pai;
    no->esq = esq;
    no->dir = dir;
    no->h = h;
    return no;
}

int getBalance(Noh* no){
    if(no == nullptr) return 0;
    return height(no->esq) - height(no->dir);
}

Noh* rotationLeft(DicAVL dicionario, Noh *x){
    Noh* paiX = x->pai;
    Noh* y = x->dir;
    Noh* filhoEsqY = y->esq;

     // Ponteiro de PaiX -> muda filho do lugar de X pra Y 
    if(paiX != nullptr){
        if(paiX->esq == x) paiX->esq = y;
        else if(paiX->dir == x) paiX->dir = y;
    } else dicionario.raiz = y;

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

Noh* rotationRight(DicAVL dicionario, Noh *y){
    Noh* paiY = y->pai;
    Noh* x = y->esq;
    Noh* filhoDirX = x->dir;

    // Ponteiro de PaiY -> muda filho do lugar de Y 
    if(paiY != nullptr){ // Atualizando ponteiro do filho do pai de Y para no lugar de y ser x
        if(paiY->esq == y) paiY->esq = x;
        else if(paiY->dir == y) paiY->dir = x;
    } else dicionario.raiz = x;

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

void atualizarAlturas(Noh* no){
    if(no != nullptr) return;
    no->h = max(height(no->esq), height(no->dir)) + 1;
    atualizarAlturas(no->pai);
}

// Retorna um ponteiro para o novo nó ou nulo se erro de alocação
Noh* inserir(DicAVL &D, TC c, TV v){
    Noh* novoNo = newNo(c, v, nullptr, nullptr, nullptr, 1);
    Noh* root = D.raiz;
    Noh* noAnterior;

    // caso a. Raiz nula => raiz é o nó
    if(root == nullptr) D.raiz = novoNo;

    // caso b. Raiz não nula => Insere e realiza balanceamento
    
    // Pega o nó a quem vou adicionar o novo nó
    while(root != nullptr){
        noAnterior = root;
        if(c < root->chave) root = root->esq;
        else if(c > root->chave) root = root->dir;
    }

    root = noAnterior;

    // Insere novo nó
    if(c < root->chave) root->esq = novoNo;
    else if(c > root->chave) root->dir = novoNo;

    // Ajuste de ponteiros de pai
    novoNo->pai = root;

    // Propagando o +1 nas alturas dos nós posteriores ao inserido e balanceando a árvore (caso esteja desbalanceada)
    do {
        root->h = max(height(root->esq), height(root->dir)) + 1;
        int balance = getBalance(root);

        if(balance > 1 && c < root->esq->chave) root = rotationRight(D, root); // Left Left Case
        else if(balance < -1 && c > root->dir->chave) root = rotationLeft(D, root); // Right Right Case
        else if(balance > 1 && c > root->esq->chave){ // Left Right Case
            root->esq = rotationLeft(D, root->esq);
            root = rotationRight(D, root);
        } else if(balance < -1 && c < root->dir->chave){ // Right Left Case
            root->dir = rotationRight(D, root->dir);
            root = rotationLeft(D, root);
        }
        root = root->pai;
        cout << root->chave;
    } while(root!=nullptr);
    return novoNo;
} 

// n aponta para o nó a ser removido
void remover(DicAVL &D, Noh *n){

} 

// Desaloca os nós da árvore.
/*void terminar (DicAVL &D){
    // acessar a raiz do dicionario e visitar em pré-ordem desalocando os nós
    Noh* no = D.raiz;

    while(no != nullptr){
        if(isLeaf(no)) free(no);
        else if(chave > c) no = no->esq;
        else if(chave < c) no = no->dir;
    }
} */