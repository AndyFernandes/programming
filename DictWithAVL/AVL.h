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

        bool isEmpty();
};

class AVL {
    public:
        int size;
        No* root;

        void rotationLeft(No no);
        void rotationRight(No no);
        bool inserir(int chave, int value);
        int search(int chave);
        bool remove(int chave);
        void preOrder(No no);
};