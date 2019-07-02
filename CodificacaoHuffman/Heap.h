#include <stdio.h>
#include <stdlib.h>  
#include<string>
#include <map>
using namespace std;
typedef map<char, int> dict;
typedef pair<char, int> par;
typedef map<char, string> tabelaSimbolos;
typedef pair<char, string> parTabela;

struct No {
    char chave;
    int qnt;
    No *filhoEsquerdo;
    No *filhoDireito;
};


class Heap {
    public:

    int heapSize;
    No** heap;

    void construir(dict tabela);
    void heapify(No** pVector, int pIndex);

    int getParent(int pIndex);

    int getLeft(int pIndex);

    int getRight(int pIndex);

    void insert(No* x);

    No* minimum();

    No* extractMinimum();

    void Swap(No** p, int pIndex, int largest);
};

No* newNo(char chave, int qnt, No* filhoEsquerdo, No* filhoDireito);
