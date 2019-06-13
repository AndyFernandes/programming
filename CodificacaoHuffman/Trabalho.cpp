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

void printArr(int arr[], int n) { 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
}

bool isLeaf(No* no){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr)
        return true;
    return false;
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim))
        result.push_back (item);

    return result;
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

No* codificaoHuffman(Heap heap){
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

tabelaSimbolos gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr){
        tabela[no->chave] = codigo;
    } else{
        tabela = gerarTabelaCodificacao(no->filhoEsquerdo, codigo + "0", tabela);
        tabela = gerarTabelaCodificacao(no->filhoDireito, codigo + "1", tabela);
    }
    return tabela;
}

string codify(char* text, tabelaSimbolos tabelaCodigos){
    string textCodify = "";
    while(*text != '\0'){
        textCodify += tabelaCodigos[*text];
        text++;
    }
    return textCodify;
}

// arquivo de saida: [num de nos | arvore | qnt de bits | # | output]
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
    // for(parTabela elemento: tabela){
    //      cout << elemento.first << " : " << elemento.second << endl;
    // }
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

void descompress(string inputFile, string outputFile){
    cout << "QQQ";
    string texto = lerArquivo(inputFile);
    vector<string> splites = split(texto, '#');
    for (int i = 0; i < splites.size(); i++){
        cout << splites[i] << "-";
    }
}

int main(int argc,char* argv[]){
    if(argc>=2) {
       string modo = argv[1];
       string inputFile = argv[2];
       string outputFile = argv[3]; 

       cout << "MODO: " << modo << endl;
       cout << "InputFile: " << inputFile << endl;
       cout << "OutputFile: " << outputFile << endl;

       if(modo == "--compress")
           compress(inputFile, outputFile);
       else if (modo == "--descompress")
            descompress(inputFile, outputFile);
    }

    
    return 0;
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
/* 
//TODO
// [num de nós | arvore | numero de bytes]
// arvore -> vector[NoArvore]
// string escreverArvore(tabelaSimbolos tabela){
//     string saida;
//     for(parTabela elemento: tabela){
//         saida += elemento.first + ":" + elemento.second + ",";
//     }
//     saida += "%#%";
//     return saida;
// }
*/