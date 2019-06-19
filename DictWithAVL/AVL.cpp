#include <stdio.h>
#include "AVL.h"

No* AVL::rotationLeft(No *x){
    No* y = x->filhoDireito;
    No* filhoEsqY = y->filhoEsquerdo;

    x->filhoEsquerdo = filhoEsqY;
    y->filhoEsquerdo = x;

    //Atualizando alturas
    if(y->filhoEsquerdo->h > (y->filhoDireito->h + 1)) y->h = y->filhoEsquerdo->h;
    else y->h = y->filhoDireito->h + 1;

    if(x->filhoEsquerdo->h > (x->filhoDireito->h + 1)) x->h = x->filhoEsquerdo->h;
    else x->h = x->filhoDireito->h + 1;

    return y; 
}

No* AVL::rotationRight(No *y){
    No* x = y->filhoEsquerdo;
    No* filhoDirX = x->filhoDireito;

    x->filhoDireito = y;
    y->filhoDireito = filhoDirX;

    //Atualizando alturas
    if(y->filhoEsquerdo->h > (y->filhoDireito->h + 1)) y->h = y->filhoEsquerdo->h;
    else y->h = y->filhoDireito->h + 1;

    if(x->filhoEsquerdo->h > (x->filhoDireito->h + 1)) x->h = x->filhoEsquerdo->h;
    else x->h = x->filhoDireito->h + 1;
    return x;
}

bool AVL::inserir(int chave, int value, No *no){
    // escrever casos

    // 1. lado 
    return true;
}

No* AVL::search(int chave, No *no){
    if(chave == null && no == nullptr)
        return -1;

    if(no->chave == chave && no == nullptr)
        return no;
    else if(no->chave > chave)
        return search(chave, no->filhoEsquerdo);
    else
        return search(chave, no->filhoDireito);
}

bool AVL::remove(int chave, No *no){
    // escrever casos
    return true;
}

void preOrder(No *no){
    if(no == nullptr) return;
    cout << no.chave << " ";
    preOrder(no->filhoEsquerdo);
    preOrder(no->filhoDireito);
}