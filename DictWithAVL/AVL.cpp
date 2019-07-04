#include <iostream>
#include <stdio.h>
#include "AVL.hpp"
using namespace std;

// Inicializa D como uma árvore vazia.
void inicializar (DicAVL &D){
    D.raiz = nullptr;
} 

// Pega a altura do nó
int height(Noh *no){
    if(no == nullptr) return 0;
    return no->h;
}

// Serve para ver qual a altura do nó, dado a altura dos seus filhos esq e dir
int max(int a, int b){
    return (a > b)? a : b;
}

// Verificar se um nó é folha
bool isLeaf(Noh* no){
    if(no->esq == nullptr && no->dir == nullptr) return true;
    return false;
}

// Aloca um novo nó
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

// Dá o fator de balanço de um nó: Está balanceado se retornar -1, 0 ou 1
int getBalance(Noh* no){ 
    if(no == nullptr) return 0;
    return height(no->esq) - height(no->dir);
}

// Realiza a rotação a Esquerda de um nó, e muda o nó do dicionário se o pai desse nó for nulo (ser a raiz)
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

// Realiza a rotação a Direita de um nó, e muda o nó do dicionário se o pai desse nó for nulo (ser a raiz)
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

// Atualiza as alturas sucessivamente dos pais até chegar a raiz
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

// Retorna o nó posterior ao nó passado (que será o sucessor do nó)
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
    bool alterouAltura = false;

    // Caso base a: é a raiz da árvore ou é um nó que tem apenas uma subarv DE 1 FOLHA esquerda ou direita 
    if(n->esq != nullptr && n->dir == nullptr){ // nó n com 1 filho esquerdo
        if(paiN == nullptr) { // n é a raiz
            D.raiz = n->esq;
            n->esq->pai = nullptr;
        } else { // nó n é um nó qualquer
            // Reatribuição de pai ao filho esq de N e o filho esq de N toma o lugar dele no pai dele
            n->esq->pai = paiN;
            if(paiN->esq != nullptr && paiN->esq->chave == n->chave) paiN->esq = n->esq;
            else if(paiN->dir != nullptr && paiN->dir->chave == n->chave) paiN->dir = n->esq;
            paiN->h = max(height(paiN->dir), height(paiN->esq)) + 1;
            alterouAltura = true;
        }
        delete(n);
        return;
    } else if(n->dir != nullptr && n->esq == nullptr){ // nó n com 1 filho direito
        if(paiN == nullptr) { // n é a raiz
            D.raiz = n->dir;
            n->dir->pai = nullptr;
        } else { // nó n é um nó qualquer
            // Reatribuição de pai ao filho dir de N e o filho dir de N toma o lugar dele no pai dele
            n->dir->pai = paiN;
            if(paiN->esq != nullptr && paiN->esq->chave == n->chave) paiN->esq = n->dir;
            else if(paiN->dir != nullptr && paiN->dir->chave == n->chave) paiN->dir = n->dir;
            paiN->h = max(height(paiN->dir), height(paiN->esq)) + 1;
            alterouAltura = true;
        }
        delete(n);
        return;
    } else if(isLeaf(n)){ // n é um nó folha
        if(paiN == nullptr) D.raiz = nullptr; // n é o nó raiz
        else { // n é um nó qualquer na árvore
            if(paiN->esq->chave == n->chave) paiN->esq = nullptr;
            else if(paiN->dir->chave == n->chave) paiN->dir = nullptr;
            paiN->h = max(height(n->pai->dir), height(n->pai->esq)) + 1;
            alterouAltura = true;
        }
        delete(n);
        return;
    } else {  // nó com 2 filhos
        Noh* temp = minNode(n->dir); // Pega o próximo nó que é maior que é folha
        // bota esse nó no lugar do n
        temp->esq = n->esq;
        temp->dir = n->dir;
        
        // atribuir ao pai de temp que agr é nullptr
        // mudar altura do pai de temp
        
        temp->pai;
    }

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