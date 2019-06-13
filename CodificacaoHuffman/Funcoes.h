#include "Heap.cpp"
#include <map>
#include <vector>
using namespace std;

class Funcoes {
    public:
        void printNo(No* no, int size);
        void printArr(int arr[], int n);
        bool isLeaf(No* no);
        vector<string> split (const string &s, char delim);
        dict countChar(char* pText);
        string lerArquivo(string path);
        No* codificaoHuffman(Heap heap);
        tabelaSimbolos gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela);
        string codify(char* text, tabelaSimbolos tabelaCodigos);
        void compress(string inputFile, string outputFile);
        void descompress(string inputFile, string outputFile);
};