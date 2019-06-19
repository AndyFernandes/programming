#include <stdio.h>
#include <stdlib.h>  
#include<string>
using namespace std;

class No {
    public:
        int chave;
        int value;
        int h;
        No *filhoEsquerdo;
        No *filhoDireito;
};

class AVL {
    public:
        int size;
        No* root;

        No* rotationLeft(No *no);
        No* rotationRight(No *no);
        bool inserir(int chave, int value);
        No* search(int chave, No* no);
        bool remove(int chave);
        void preOrder(No* no);
};