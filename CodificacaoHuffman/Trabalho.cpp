#include <iostream>
#include <map>
#include "Heap.cpp"
#include <set>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cstring>
using namespace std;

void printNo(No* no, int size){
    for(No* i = no; i != no+size; i ++){
        cout << i->chave << " : " << i->qnt << endl;
    }
}

dict countChar(char* pText){
    dict m;
    while(*pText != '\0'){
        if (m[*pText])
            m[*pText] += 1;
        else
            m[*pText] = 1;
        pText++;
    }
    return m;
}

string lerArquivo(string path){
    string text;
    string line;
    ifstream myfile (path); // ifstream = padrão ios:in
    if (myfile.is_open()){
        while (! myfile.eof()){ //enquanto end of file for false continua
            getline (myfile, line); // como foi aberto em modo texto(padrão)
            text += line; //e não binário(ios::bin) pega cada linha
        }
        myfile.close();
        return text;
    }
    else cout << "Unable to open file";
    return "";
}

No* codificaoHuffman(Heap heap){
    No* left;
    No* right;
    No sum;
    while(heap.heapSize != 1){
        //cout << "left: " << heap.heap->chave  << " : " << heap.heap->qnt << endl;
        left = heap.extractMinimum();
        //cout << "right: " << heap.heap->chave  << " : " << heap.heap->qnt << endl;
        right = heap.extractMinimum();
        //cout << "----------------" << endl;
        sum.chave = '%';
        sum.qnt = left->qnt + right->qnt;
        sum.filhoEsquerdo = left;
        sum.filhoDireito = right;
        heap.insert(sum);
    }
    return heap.extractMinimum();
}

// nao ta printandooooooo
// https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/huffman.html
tabelaSimbolos gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela){
    if(no->filhoEsquerdo != nullptr){
        cout << no->filhoEsquerdo->chave <<endl;
        gerarTabelaCodificacao(no->filhoEsquerdo, codigo+"0", tabela);
    }
    cout << "NULO";
    cout << no->filhoEsquerdo->chave <<endl;
    
    /*if(!no->filhoDireito && !no->filhoEsquerdo){
        //tabela[no->chave] = codigo;
        cout << no->chave << " : " << codigo << endl; 
    } else{
        tabela = gerarTabelaCodificacao(no->filhoEsquerdo, codigo + "0", tabela);
        tabela = gerarTabelaCodificacao(no->filhoDireito, codigo + "1", tabela);
    }*/
    return tabela;
}

/* 
LÓGICA:
    # PARTE 1: Codificar
    1. Primeiro construir um dicionário que conta a ocorrencia de cada caractere
    2. Depois construir uma heap, repassando o dicionário 
        -> Ajeitar minha heap para suportar a estrutura de nós -> sempre ordenará olhando pela quantidade
    
    3. Algoritmo de Huffman -> retorno um nó (o único restante)
    4. A partir desse nó iremos gerar a tabelinha de símbolos
    5. Ai agora seria codificar o arquivo/string

    ------------------------------

    # PARTE 2: Decodificar
    

*/
int main(){
    // int vetor[] =  {28,58,49,69,52,69,40,75,71,82};
    // int vetor[] =  {4,1,3,2,16,9,10,14,8,7};
    Heap heap;
    // heap.construir(vetor, 10);
    // // print_vector(vetor, vetor+15);
    // print_vector(heap.heap, heap.heap + heap.heapSize);
    // cout << "Minimo " << heap.minimum() << endl;
    // int min = heap.extractMinimum();
    // cout << "Minimo " << min << endl;
    // print_vector(heap.heap, heap.heap + heap.heapSize);

    // heap.insert(3);
    // heap.insert(50);
    // heap.insert(7);
    // heap.insert(6);    
    // dict countSymbols;
    // m['A'] = 2;
    ///// teste do dia 08/06 
    /*char c[] = "batatinha quando nasce esparrama pelo chao";
    dict countSymbols = countChar(c);
    
    heap.construir(countSymbols);

    No min = heap.minimum();
    cout << "MINIMO:" << min.chave << " : " << min.qnt << endl;


    No* no = (No*)malloc(sizeof(No)*countSymbols.size());
    No* i = no;
    for(par element: countSymbols){
        //cout << element.first << " : " << element.second << endl;
        i->chave = element.first;
        i->qnt =  element.second;
        i++;
    //    heap.insert(element.second);
    }
    printNo(no, countSymbols.size());
    cout << "\n\n" << no[1].qnt;*/

    
    /*no->chave = 'a';
    //cout << no->chave << endl;
    no++;
    no->chave = 'b';
    no++;
    no->chave = 'c';
    no--;
    no--;
    printNo(no);*/

    //cout << no->chave;

    //cout << "HEAP MINIMUM: " << min->qnt << " | " << min->chave;

    /////////////// testes dia 09

    string texto = lerArquivo("teste.txt");
    cout << texto << endl;
    char c[texto.size() + 1];
    strcpy(c, &texto[0]);
    dict countSymbols = countChar(c);
    
    heap.construir(countSymbols);
    cout << "a: " << heap.heap->chave  << " : " << heap.heap->qnt << endl;
    No* min = codificaoHuffman(heap);
    tabelaSimbolos tabela;
    //tabela = gerarTabelaCodificacao(min, "", tabela);
    //for(parTabela elemento: tabela){
    //    cout << elemento.first << " : " << elemento.second << endl;
    //}
    //cout << "MINIMO:" << min->chave << " : " << min->qnt << endl;
    //cout << "a: " << heap.heap->chave  << " : " << heap.heap->qnt << endl;
    return 0;
}