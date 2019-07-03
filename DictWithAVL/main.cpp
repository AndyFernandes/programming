#include <iostream>
#include "AVL.cpp"
using namespace std;

void preOrder(Noh *root){  
    if(root != NULL)  {  
        cout << "CHAVE: " << root->chave;
        if(root->pai != nullptr) cout << " | PAI: " << root->pai->chave;
        if(root->esq != nullptr) cout << " | ESQ: " << root->esq->chave;
        if(root->dir != nullptr) cout << " | DIR: " << root->dir->chave;
        cout << endl;  
        preOrder(root->esq);  
        preOrder(root->dir);  
    }  
} 

int main(){
    DicAVL dicionario;
    inicializar(dicionario);
    ///////////////////////////////  TESTES INSERÇÃO /////////////////////////////
    Noh* no = inserir(dicionario, 10, 10);
    no = inserir(dicionario, 20, 10);
    no = inserir(dicionario, 5, 5);
    no = inserir(dicionario, 30, 10);
    no = inserir(dicionario, 40, 10);
    no = inserir(dicionario, 50, 10);
    no = inserir(dicionario, 2, 10);
    // Noh *no1 = inserir(dicionario, 204, -21);
    // Noh *no2 = inserir(dicionario, 169.75, 59.5);
    // Noh *no3 = inserir(dicionario, 246.75, -60);
    // Noh *no4 = inserir(dicionario, -98.75, 53.5);
    // Noh *no5 = inserir(dicionario, -133.25, 10.5);
    // Noh *no6 = inserir(dicionario, -13.5, 25.5);
    // Noh *no7 = inserir(dicionario, -81, 2.5);
    // Noh *no8 = inserir(dicionario, 271.25, 83);
    // Noh *no9 = inserir(dicionario, 182.5, -68.5);
    // Noh *no10 = inserir(dicionario, -59.25, -74);
    // Noh *no11 = inserir(dicionario, -234.5, 99.5);
    no = inserir(dicionario, 25, 10);
    preOrder(dicionario.raiz);  

    ///////////////////////////////  TESTES PROCURAR /////////////////////////////
    // cout << endl << endl << endl;
    // no = procurar(dicionario, 10);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, 230);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, 169.75);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, 246.75);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, 271.25);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -81);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -234.5);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, 182.5);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, 204);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -13.5);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -133.25);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -98.75);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -169.75);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    // no = procurar(dicionario, -59.25);
    // if(no != nullptr) cout << "CHAVE: "  << no->chave << " | " << no->valor << endl;
    
    ///////////////////////////////  TESTES REMOÇÃO /////////////////////////////
    
    // remover(dicionario, no3);
    // remover(dicionario, no8);
    // remover(dicionario, no7);
    // remover(dicionario, no11);
    // remover(dicionario, no9);
    // remover(dicionario, no1);
    // remover(dicionario, no6);
    // remover(dicionario, no5);
    // remover(dicionario, no4);
    // remover(dicionario, no11);
    // remover(dicionario, no2);
    
    cout << endl << endl;
    terminar(dicionario);
    return 0;
}