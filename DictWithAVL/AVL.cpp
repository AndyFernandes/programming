#include <iostream>
#include <stdio.h>
#include "avl.hpp"
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

int calcularAltura(Noh *raiz){

    if(!raiz->dir) {
      if(!raiz->esq){
        return 1;
      }else{
          return raiz->esq->h + 1;
      }
    }else if(!raiz->esq) {
        if(!raiz->dir){
            return 1;
        }else{
            return raiz->dir->h + 1;
        }
    }else if(raiz->esq->h > raiz->dir->h){
        return raiz->esq->h + 1;
    } else{
        return raiz->dir->h +1;
    }
}

// Retorna um ponteiro para o novo nó ou nulo se erro de alocação
Noh* inserir(DicAVL &D, TC c, TV v){
    cout << "Insercao da chave: " << c << " : " << v << endl;
    // procurar no
    Noh* noBusca = D.raiz;

    while(noBusca != nullptr){
        TC chave = noBusca->chave;
        // cout << no->chave;
        if(chave == c) break;
        else if(chave > c) noBusca = noBusca->esq;
        else if(chave < c) noBusca = noBusca->dir;
    }

    if(noBusca != nullptr){
        cout << "No com chave = " << c << " ja existente!" << endl;
        return nullptr;
    }

    Noh* novoNo = newNo(c, v, 1);
    Noh* root = D.raiz;
    Noh* noAnterior = nullptr;
    bool ladoAdicionado = true; // true -> lado esquerdo & false -> lado direito
   
    // caso a. Raiz nula => raiz é o nó
    if(root == nullptr){
        D.raiz = novoNo;
        cout << "novoNo h:" << novoNo->h << endl;
        return novoNo;
    } 
    // caso b. Raiz não nula => Insere e realiza balanceamento
    // Pega o nó a quem vou adicionar o novo nó
    while(root != nullptr){
        noAnterior = root;
        if(c < root->chave)root = root->esq;
        else if(c > root->chave) root = root->dir;
    }

    // cout << "CHAVE NOANT" << noAnterior->chave << "NOANT->h" << noAnterior->h << endl << endl;
    root = noAnterior;
    
    // Ajuste de ponteiros de pai
    novoNo->pai = root;

    // Insere novo nó
    if(c < root->chave) root->esq = novoNo;
    else if(c > root->chave) root->dir = novoNo;
    
    // Propagando o +1 nas alturas dos nós posteriores ao inserido e balanceando a árvore (caso esteja desbalanceada)
    do {
        // cout << "1 - CHAVE ROOT" << root->chave << "ROOT->h" << root->h << endl;
        root->h = max(height(root->esq), height(root->dir)) + 1;
        // cout << "2 - CHAVE ROOT" << root->chave << "ROOT->h" << root->h << endl;
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
        // cout << "3 - CHAVE ROOT" << root->chave << "ROOT->h" << root->h << endl;
        // cout << "----------------------" << endl << endl;
        root->h = max(height(root->esq), height(root->dir)) + 1;
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
    cout << "REMOCAO do no com chave: " << n->chave << endl;
    
    // Noh* root = D.raiz;
    // cout << "PASEEI AQUI -1";
    int balance;
    // se a raiz for nula.. nada a remover
    if(D.raiz == nullptr) return;
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
            alterouAltura = true; // tem de alterar a altura do pai de N
        }
    } else if(n->dir != nullptr && n->esq == nullptr){ // nó n com 1 filho direito
        if(paiN == nullptr) { // n é a raiz
            D.raiz = n->dir;
            n->dir->pai = nullptr;
        } else { // nó n é um nó qualquer
            // Reatribuição de pai ao filho dir de N e o filho dir de N toma o lugar dele no pai dele
            n->dir->pai = paiN;
            if(paiN->esq != nullptr && paiN->esq->chave == n->chave) paiN->esq = n->dir;
            else if(paiN->dir != nullptr && paiN->dir->chave == n->chave) paiN->dir = n->dir;
            alterouAltura = true; // tem de alterar a altura do pai de N
        }
    } else if(isLeaf(n)){ // n é um nó folha
        if(paiN == nullptr){
            D.raiz = nullptr; // n é o nó raiz
        } 
        else { // n é um nó qualquer na árvore
            if(paiN->esq != nullptr && paiN->esq->chave == n->chave) paiN->esq = nullptr;
            else if(paiN->dir != nullptr && paiN->dir->chave == n->chave) paiN->dir = nullptr;
            alterouAltura = true; // tem de alterar a altura do pai de N
        }
    } else {  // nó com 2 filhos
        // PROFESSOR POR FAVOR OLHA AQUI
        // botar esse nó TEMP no lugar do n
        Noh* temp = minNode(n->dir); // Pega o próximo nó que é maior que é folha
        Noh* paiTemp = temp->pai;

        // Inicio das modificações necessárias de ponteiros: Terei de mexer em 5 nós
        // TEMP: atualizar seu pai e seus filhos
        // FILHO ESQ e DIR de N -> atualizar o seu pai para TEMP
        // PAI DE N -> atualizar seu filho n para temp
        // PAI DE TEMP -> zerar o ponteiro pro seu filho esquerdo

        // FILHOS DE N
        // 1o: Atualiza filhos de n pro pai deles agora ser temp
        n->esq->pai = temp;
        temp->esq = n->esq;
        if(n->dir != temp){ 
            temp->dir = n->dir;
            n->dir->pai = temp;
        } else{
            temp->dir = nullptr;
            n->dir->pai = paiN; // mas isso meio que é duplicado na linha 276
        } 

        // PAI DE TEMP
        // 2o atribuir ao pai de temp que o filho que era tempp agr é nullptr
        if(paiTemp != nullptr) paiTemp->esq = nullptr;

        // PAI DE N = atribuição de filho do PAIN agora pra ser temp e atribuição do novo pai de temp
        temp->pai = paiN;
        if(paiN != nullptr){
            // vendo qual filho n era do pai dele: se era esq ou direito
            if(paiN->esq == n) paiN->esq = temp;
            else if(paiN->dir == n) paiN->dir = temp;
        } else D.raiz = temp;
     
        // mudar altura do pai de temp
        if(paiTemp && paiTemp != n) paiN = paiTemp;
        else paiN = temp;
        alterouAltura = true;
    }
    delete(n);
    if(alterouAltura){
        do {
            // cout << "Passei aqui2";
            paiN->h = 1 + max(height(paiN->esq), height(paiN->dir));
            balance = getBalance(paiN);
            if(balance > 1 && getBalance(paiN->esq) >= 0){
                // cout << "IF 1" << endl;
                paiN = rotationRight(D, paiN); //Left Left Case
            } 
            else if(balance < -1 && getBalance(paiN->dir) <= 0){
                // cout << "IF 2" << endl;
                paiN = rotationLeft(D, paiN); // Right Right Case
            } 
            else if(balance > 1 && getBalance(paiN->esq) < 0){ // Left Right Case
                // cout << "IF 3" << endl;
                paiN->esq = rotationLeft(D, paiN->esq);
                paiN = rotationRight(D, paiN);
            } else if(balance < -1 && getBalance(paiN->dir) > 0){ // Right Left Case
                // cout << "IF 4" << endl;              
                paiN->dir = rotationRight(D, paiN->dir);
                paiN = rotationLeft(D, paiN);
            }
            paiN->h = 1 + max(height(paiN->esq), height(paiN->dir));
            paiN = paiN->pai;
        } while(paiN != nullptr);
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