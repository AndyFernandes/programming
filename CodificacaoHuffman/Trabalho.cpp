#include <iostream>
#include <map>
#include "Heap.cpp"
#include <set>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
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

// https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/huffman.html
tabelaSimbolos gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr){
        tabela[no->chave] = codigo;
        //cout << no->chave << " : " << codigo << endl; 
    } else{
        tabela = gerarTabelaCodificacao(no->filhoEsquerdo, codigo + "0", tabela);
        tabela = gerarTabelaCodificacao(no->filhoDireito, codigo + "1", tabela);
    }
    return tabela;
}

//TODO
// [num de nós | arvore | numero de bytes]
// arvore -> vector[NoArvore]
string escreverArvore(tabelaSimbolos tabela){
    string saida;
    for(parTabela elemento: tabela){
        saida += elemento.first + ":" + elemento.second + ",";
    }
    saida += "%#%";
    return saida;
}

//TODO
void compress(string inputFile, string outputFile){
    Heap heap;
    string texto = lerArquivo(inputFile);
    char c[texto.size() + 1];
    strcpy(c, &texto[0]);
    dict countSymbols = countChar(c);
    
    heap.construir(countSymbols);
    No* no = codificaoHuffman(heap);
    tabelaSimbolos tabela;
    tabela = gerarTabelaCodificacao(no, "", tabela);
    //string arvore = escreverArvore(tabela);   
    //string textoCodificado = codificando(escreverArvore(tabela), texto);
    outputFile.open(outputFile);
    outputFile << textoCodificado;
    outputFile.close();
    cout << "Done!\n";
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
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
    6. Gravar a arvore no inicio do arquivo: -> separar por ',' as tuplas, e char:code 
        a:qnt,b:qnt
    ------------------------------

    # PARTE 2: Decodificar
    1. Ler arquivo em uma string
    2. Splitar string por '%#%' 
    3. Reconstruir tabela de simbolos
    4. Decodificar
    5. Gravar o arquivo
*/

int main(int argc,char* argv[]){
    /*if(argc>=2) {
       string modo = argv[1];
       string inputFile = argv[2];
       string outputFile = argv[3]; 

       cout << "MODO: " << modo << endl;
       cout << "InputFile: " << inputFile << endl;
       cout << "OutputFile: " << outputFile << endl;

       if(modo == "--compress"){

       } else if (modo == "--decompress"){}
    } */

    Heap heap;
    string texto = lerArquivo("teste.txt");
    cout << texto << endl;
    char c[texto.size() + 1];
    strcpy(c, &texto[0]);
    dict countSymbols = countChar(c);
    
    heap.construir(countSymbols);
    No* min = codificaoHuffman(heap);
    tabelaSimbolos tabela;
    tabela = gerarTabelaCodificacao(min, "", tabela);
    for(parTabela elemento: tabela){
        cout << elemento.first << " : " << elemento.second << endl;
    }

    return 0;
}