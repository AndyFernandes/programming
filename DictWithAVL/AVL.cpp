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

    // Ponteiro de PaiX -> muda filho do lugar de X pra Y 
    if(paiX != nullptr){
        if(paiX->esq == x) paiX->esq = y;
        else if(paiX->dir == x) paiX->dir = y;
    } else dicionario.raiz = y;
    
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

    // Ponteiro de PaiY -> muda filho do lugar de Y 
    if(paiY != nullptr){ // Atualizando ponteiro do filho do pai de Y para no lugar de y ser x
        if(paiY->esq == y) paiY->esq = x;
        else if(paiY->dir == y) paiY->dir = x;
    } else dicionario.raiz = x;

    // Filho direito de Y -> muda pai
    if(filhoDirX != nullptr) filhoDirX->pai = y;
  
    // X -> muda pai e muda filho direito
    if(x != nullptr) x->pai = paiY;
    if(x != nullptr) x->dir = y; // Y é agora filho direito de y
   
    // Y -> muda pai e muda filho esquerdo
    if(y != nullptr) y->pai = x; // X agora é o pai de y
    if(y != nullptr) y->esq = filhoDirX; // Filho Direito de X agora vira filho Esquerdo de Y
    
   
    //Atualizando alturas
    if(y!=nullptr) y->h = max(height(y->esq), height(y->dir)) + 1;
    if(x!= nullptr) x->h = max(height(x->esq), height(x->dir)) + 1;
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

    cout << "Chave "<< c <<" nao encontrado!" << endl;
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
        if(c < root->chave)root = root->esq;
        else if(c > root->chave) root = root->dir;
    }

    root = noAnterior;
    // Ajuste de ponteiros de pai
    novoNo->pai = root;

    // Insere novo nó
    if(c < root->chave) root->esq = novoNo;
    else if(c > root->chave) root->dir = novoNo;
    
    // Propagando o +1 nas alturas dos nós posteriores ao inserido e balanceando a árvore (caso esteja desbalanceada)
    do {
        root->h = max(height(root->esq), height(root->dir)) + 1;
        int balance = getBalance(root);

        if(balance > 1 && c < root->esq->chave) root = rotationRight(D, root); // Left Left Case
        else if(balance < -1 && c > root->dir->chave) root = rotationLeft(D, root); // Right Right Case
        else if(balance > 1 && c > root->esq->chave){ // Left Right Case
            root->esq = rotationLeft(D, root->esq);
            root = rotationRight(D, root);
        }else if(balance < -1 && c < root->dir->chave){ // Right Left Case 
            root->dir = rotationRight(D, root->dir);
            root = rotationLeft(D, root);
        }
        root = root->pai;
    } while(root != nullptr);
    return novoNo;
} 

// Retorna o nó maissss a esquerda do nó passado
Noh* minNode(Noh* no){
    Noh* corrente = no;
    while(corrente->esq != nullptr) corrente = corrente->esq;
    return corrente;
}

// n aponta para o nó a ser removido
void remover(DicAVL &D, Noh *n){
    if(n == nullptr) return;

    Noh* root = D.raiz;
    int balance;
    // se a raiz for nula.. nada a remover
    if(root == nullptr) return;

    // Verificando se o nó realmente pertence ao dicionário
    n = procurar(D, n->chave);
    if(n == nullptr) return;
    Noh* paiN = n->pai;

    // Caso base a: é a raiz da árvore ou é um nó que tem apenas uma subarv DE 1 FOLHA esquerda ou direita 
    // a.1. É A RAIZ 
    if(paiN == nullptr){
        if(n->esq != nullptr && n->dir == nullptr && n->esq->esq == nullptr && n->esq->dir == nullptr){ // nó raiz com 1 filho
            D.raiz = n->esq;
            n->esq->pai = nullptr;
            delete(n);
            return;
        } else if(n->dir != nullptr && n->esq == nullptr && n->dir->esq == nullptr && n->dir->dir == nullptr){ // nó raiz com 1 filho
            D.raiz = n->dir;
            n->dir->pai = nullptr;
            delete(n);
            return;
        } else if(n->dir == nullptr && n->esq == nullptr){ // nó raiz sem filhos
            D.raiz = nullptr;
            delete(n);
            return;
        }
    } 
    //  DUVIDAS A PARTIR DAQUIIIIIII
    else { // a.2. NÃO É A RAIZ -> Basicamente são os casos de remoção que mexem (talvez) na altura da árvore, porém ainda continua AVL
        // TODO PERGUNTAR ISSO AO PABLO -> PQ PODE SER AQUI QUE ELE POSSA TER UMA SUBARV DIR E ESQ E NÃO NECESSARIAMENTE NULA
        // acho que eu to confundindo
        if(n->esq != nullptr && n->dir == nullptr && isLeaf(n->esq)){ // Mas possui apenas 1 filho esquerdo, que é folha
            // Reatribuição de pai ao filho esq de N e o filho esq de N toma o lugar dele no pai dele
            n->esq->pai = paiN;
            if(paiN->esq->chave == n->chave) paiN->esq = n->esq;
            else if(paiN->dir->chave == n->chave) paiN->dir = n->esq;
            paiN->h = max(height(paiN->dir), height(paiN->esq)) + 1;
            delete(n);
            return;
        } else if(n->dir != nullptr && n->esq == nullptr && n->dir->esq == nullptr && n->dir->dir == nullptr){ // Mas possui apenas 1 filho direito, que é folha
            n->dir->pai = paiN;
            if(paiN->esq->chave == n->chave) paiN->esq = n->dir;
            else if(paiN->dir->chave == n->chave) paiN->dir = n->dir;
            paiN->h = max(height(paiN->dir), height(paiN->esq)) + 1;
            delete(n);
            return;
        } else if(isLeaf(n)){ // nó sem filhos -> CASO DO NÓ FOLHA: CASO 2
            if(paiN->esq->chave == n->chave) paiN->esq = nullptr;
            else if(paiN->dir->chave == n->chave) paiN->dir = nullptr;
            paiN->h = max(height(n->pai->dir), height(n->pai->esq)) + 1;
            delete(n);
            return;
         } else { // nó com 2 filhos
            Noh* temp = minNode(n->dir); // Pega o próximo nó que é maior que o nó n
            do {
                balance = getBalance(n);
                if(balance > 1 && getBalance(n->esq) >= 0) n = rotationRight(D, n); //Left Left Case
                if(balance < -1 && getBalance(n->dir) <= 0) n = rotationLeft(D, n); // Right Right Case
                if(balance > 1 && getBalance(n->esq) < 0){
                    n->esq = rotationLeft(D, n->esq);
                    n = rotationRight(D, n);
                }
                if(balance < -1 && getBalance(n->dir) > 0){
                    n->dir = rotationRight(D, n->dir);
                    n = rotationLeft(D, n);
                }
            } while(n != nullptr);
        }
    }
}

void desalloc(Noh* node){
    if(node == nullptr) return;
    desalloc(node->esq);
    desalloc(node->dir);
    cout << "No desalocado: " << node->chave << endl;
    delete(node);
}

// Desaloca os nós da árvore.
void terminar (DicAVL &D){
    // acessar a raiz do dicionario e visitar em pré-ordem desalocando os nós
    Noh* no = D.raiz;
    desalloc(no);
    D.raiz = nullptr;
}