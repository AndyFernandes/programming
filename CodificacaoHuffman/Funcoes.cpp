#include "Funcoes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

void Funcoes::printNo(No* no, int size){
    for(No* i = no; i != no+size; i ++){
        cout << i->chave << " : " << i->qnt << endl;
    }
}

void Funcoes::printArr(int arr[], int n) { 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
}

bool Funcoes::isLeaf(No* no){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr)
        return true;
    return false;
}

vector<string> Funcoes::split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim))
        result.push_back (item);

    return result;
}

dict Funcoes::countChar(char* pText){
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

string Funcoes::lerArquivo(string path){
    string text;
    string line;
    ifstream myfile (path); 
    if (myfile.is_open()){
        while (! myfile.eof()){ 
            getline (myfile, line); 
            text += line; 
        }
        myfile.close();
        return text;
    }
    else cout << "Unable to open file";
    return "";
}

No* Funcoes::codificaoHuffman(Heap heap){
    No* left;
    No* right;
    No sum;
    while(heap.heapSize != 1){
        left = heap.extractMinimum();
        right = heap.extractMinimum();
        sum.chave = '%';
        sum.qnt = left->qnt + right->qnt;
        sum.filhoEsquerdo = left;
        sum.filhoDireito = right;
        heap.insert(sum);
    }
    return heap.extractMinimum();
}

tabelaSimbolos Funcoes::gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr){
        tabela[no->chave] = codigo;
    } else{
        tabela = gerarTabelaCodificacao(no->filhoEsquerdo, codigo + "0", tabela);
        tabela = gerarTabelaCodificacao(no->filhoDireito, codigo + "1", tabela);
    }
    return tabela;
}

string Funcoes::codify(char* text, tabelaSimbolos tabelaCodigos){
    string textCodify = "";
    while(*text != '\0'){
        textCodify += tabelaCodigos[*text];
        text++;
    }
    return textCodify;
}

// arquivo de saida: [num de nos | arvore | qnt de bits | # | output]
void Funcoes::compress(string inputFile, string outputFile){
    Heap heap;
    string texto = lerArquivo(inputFile);
    char c[texto.size() + 1];
    strcpy(c, &texto[0]);
    dict countSymbols = countChar(c);
    for(par elemento: countSymbols){
         cout << elemento.first << " : " << elemento.second << endl;
    }
    heap.construir(countSymbols);
    No* no = codificaoHuffman(heap);
    tabelaSimbolos tabela;
    tabela = gerarTabelaCodificacao(no, "", tabela);
    for(parTabela elemento: tabela){
         cout << elemento.first << " : " << elemento.second << endl;
    }
    ofstream outfile;
    outfile.open(outputFile);
    string arvore; //= escreverArvore(tabela);  
    string textCodify = codify(c, tabela);

    outfile << heap.heapSize << ",";
    outfile << arvore << ",";
    //outfile << qntbits;
    outfile << "#";
    outfile << textCodify;

    outfile.close();
    cout << "Done!\n";
}

void Funcoes::descompress(string inputFile, string outputFile){
    string texto = lerArquivo(inputFile);
    vector<string> splites = split(texto, '#');
    for (int i = 0; i < splites.size(); i++){
        cout << splites[i] << "-";
    }
}