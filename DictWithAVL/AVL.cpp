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

Noh* newNo(TC chave, TV value, int h){
    Noh *no = new Noh();
    no->chave = chave;
    no->valor = value;
    no->pai = nullptr;
    no->esq = nullptr;
    no->dir = nullptr;
    no->h = h;
    return no;
}

int getBalance(Noh* no){ // Dá o fator de balanço de um nó: Está balanceado se retornar -1, 0 ou 1
    if(no == nullptr) return 0;
    return height(no->esq) - height(no->dir);
}

Noh* rotationLeft(DicAVL &dicionario, Noh *x){
    Noh* paiX = x->pai;
    Noh* y = x->dir;
    Noh* filhoEsqY = y->esq;

    // cout << "PASSEI AQUI LEFT" << endl;
     // Ponteiro de PaiX -> muda filho do lugar de X pra Y 
    if(paiX != nullptr){
        if(paiX->esq == x) paiX->esq = y;
        else if(paiX->dir == x) paiX->dir = y;
    } else{
        // cout << "ENTREI AQUI" << endl;
        dicionario.raiz = y;
    } 

    // Filho direito de Y -> muda pai
    if(filhoEsqY != nullptr) filhoEsqY->pai = x;

    // X -> muda pai e muda filho direito
    if(x != nullptr) x->pai = y;
    if(x != nullptr) x->dir = filhoEsqY;

    // Y -> muda pai e muda filho esquerdo
    if(y != nullptr) y->pai = paiX;
    if(y != nullptr) y->esq = x; 
    
    //Atualizando alturas
    if(y !=nullptr) y->h = max(height(y->esq), height(y->dir)) + 1;
    if(x != nullptr) x->h = max(height(x->esq), height(x->dir)) + 1;

    return y; 
}

Noh* rotationRight(DicAVL &dicionario, Noh *y){
    Noh* paiY = y->pai; 
    Noh* x = y->esq;
    Noh* filhoDirX = x->dir; 

    // cout << "PASSEI AQUI RIGHT" << endl;
    // cout << "Y CHAVE: " << y->chave;

    // Ponteiro de PaiY -> muda filho do lugar de Y 
    if(paiY != nullptr){ // Atualizando ponteiro do filho do pai de Y para no lugar de y ser x
        if(paiY->esq == y) paiY->esq = x;
        else if(paiY->dir == y) paiY->dir = x;
        // cout << "Passei daqui " << endl;
    } else dicionario.raiz = x;

    // Filho direito de Y -> muda pai
    if(filhoDirX != nullptr) filhoDirX->pai = y;
    // cout << "Passei daqui 2" << endl;
    // X -> muda pai e muda filho direito
    if(x != nullptr) x->pai = paiY;
    if(x != nullptr) x->dir = y; // Y é agora filho direito de y
    // cout << "Passei daqui 3" << endl;
    // Y -> muda pai e muda filho esquerdo
    if(y != nullptr) y->pai = x; // X agora é o pai de y
    if(y != nullptr) y->esq = filhoDirX; // Filho Direito de X agora vira filho Esquerdo de Y
    
    // cout << "Passei daqui 4" << endl;
    //Atualizando alturas
    if(y!=nullptr) y->h = max(height(y->esq), height(y->dir)) + 1;
    if(x!= nullptr) x->h = max(height(x->esq), height(x->dir)) + 1;
    // cout << "Y->h " << y->h << endl;
    // cout << "X->h " << x->h << endl;
    
    return x;
}

// Retorna um ponteiro para o nó da chave procurada, ou nulo se a chave não estiver em D.
Noh* procurar(DicAVL &D, TC c){
    Noh* no = D.raiz;

    while(no != nullptr){
        TC chave = no->chave;
        // cout << no->chave;
        if(chave == c) return no;
        else if(chave > c) no = no->esq;
        else if(chave < c) no = no->dir;
    }

    cout << "No nao encontrado!" << endl;
    return nullptr;
}

void atualizarAlturas(Noh* no){
    if(no != nullptr) return;
    no->h = max(height(no->esq), height(no->dir)) + 1;
    atualizarAlturas(no->pai);
}

// Retorna um ponteiro para o novo nó ou nulo se erro de alocação
Noh* inserir(DicAVL &D, TC c, TV v){
    cout << "Insercao da chave: " << c << " : " << v << endl;
    Noh* novoNo = newNo(c, v, 1);
    Noh* root = D.raiz;
    Noh* noAnterior = nullptr;
    bool ladoAdicionado = true; // true -> lado esquerdo & false -> lado direito
   
    // caso a. Raiz nula => raiz é o nó
    if(root == nullptr){
        D.raiz = novoNo;
        return novoNo;
    } 
    
    // caso b. Raiz não nula => Insere e realiza balanceamento
    
    // Pega o nó a quem vou adicionar o novo nó
    while(root != nullptr){
        noAnterior = root;
        // cout << "Passei aqui 2" << endl;
        if(c < root->chave){
            root = root->esq;
            ladoAdicionado = true;
        } else if(c > root->chave){
            root = root->dir;
            ladoAdicionado = false;
        }
    }

    root = noAnterior;

    // Ajuste de ponteiros de pai
    novoNo->pai = root;

    // Insere novo nó
    if(c < root->chave) root->esq = novoNo;
    else if(c > root->chave) root->dir = novoNo;

    // Propagando o +1 nas alturas dos nós posteriores ao inserido e balanceando a árvore (caso esteja desbalanceada)
    do {
        // cout << "Passei aqui3" << endl;
        root->h = max(height(root->esq), height(root->dir)) + 1;
        // cout << root->h << endl;
        int balance = getBalance(root);
        // cout << balance << endl;

        if(balance > 1 && c < root->esq->chave){
        // if(balance > 1 && ladoAdicionado == true){
            cout << "IF 1" << endl;
            root = rotationRight(D, root); // Left Left Case
        } else if(balance < -1 && c > root->dir->chave){
        // else if(balance < -1 && ladoAdicionado == false){
            cout << "IF 2" << endl;
            // cout << root-> chave << endl;
            root = rotationLeft(D, root); // Right Right Case
        } else if(balance > 1 && c > root->esq->chave){ // Left Right Case
        // else if(balance > 1 && ladoAdicionado == false){ // Left Right Case
            cout << "IF 3" << endl;
            root->esq = rotationLeft(D, root->esq);
            root = rotationRight(D, root);
        }else if(balance < -1 && c < root->dir->chave){ // Right Left Case 
        // else if(balance < -1 && ladoAdicionado == true){ // Right Left Case
            cout << "IF 4" << endl;
            // cout << root->chave << endl;
            root->dir = rotationRight(D, root->dir);
            root = rotationLeft(D, root);
        }
        root = root->pai;
        // if(root != nullptr) cout << root->chave << endl;
    } while(root != nullptr);
    // cout << "Passei aqui4" << endl;
    return novoNo;
} 

// Retorna o nó maissss a esquerda do nó passado
Noh* minNode(Noh* no){
    Noh* corrente = no;
    while(corrente->esq != nullptr)
        corrente = corrente->esq;
    return corrente;
}

// n aponta para o nó a ser removido
/*void remover(DicAVL &D, Noh *n){
    Noh* root = D.raiz;
    Noh* noAnterior = nullptr;
    int balance;
    // se a raiz for nula.. nada a remover
    if(root == nullptr) return;

    // Verificando se o nó realmente pertence ao dicionário
    Noh* n = procurar(D, n->chave);
    if(n == nullptr) return;

    // Caso base: é a raiz da árvore ou é um nó que tem apenas uma subarv esquerda ou direita
    if(n->pai == nullptr && n->esq != nullptr && n->dir == nullptr){ // nó raiz com 1 filho
        D.raiz = n->esq;
        n->esq->pai = nullptr;
        free(n);
        return;
    } else if(n->pai == nullptr && n->dir != nullptr && n->esq == nullptr){ // nó raiz com 1 filho
        D.raiz = n->dir;
        n->dir->pai = nullptr;
        free(n);
        return;
    } else if(n->pai == nullptr && n->dir == nullptr && n->esq == nullptr){ // nó raiz sem filhos
        D.raiz = nullptr;
        free(n);
        return;
    } else { // nó com 2 filhos
        Noh* temp = minNode(n->dir);

        do {
            balance = getBalance(n);
            if(balance == 1 || balance == 0){
                if(n->dir->h > n->esq->h){ // pega o nó da árvore direita pra substituir x
                    
                } else { // pega o nó da árvore esquerda pra substituir x

                }
            }

        } while(n != nullptr);
    }

    // Case base2: é um nó folha
    if(isLeaf(n)){
        free(n);
        if(n->pai->esq == n) n->pai->esq = nullptr;
        else if(n->pai->dir == n) n->pai->dir = nullptr;
        // TODO: atualizar altura do resto da árvore
        // TODO2: Ver se é necessário balancear
    }




    do{

    }while();



} */

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