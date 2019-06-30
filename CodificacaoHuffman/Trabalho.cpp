#include <iostream>
#include "Heap.cpp"
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;

#define bytes 8
#define internNode '%' // indica nó interno
#define indicadorNulo '#' // indica nó nulo
#define indicadorFolha '$' // indica nó folha

void printNo(No* no, int size){
    for(No* i = no; i != no+size; i ++)
        cout << i->chave << " : " << i->qnt << endl;
}

bool isLeaf(No* no){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr) return true;
    return false;
}

No* newNo(char chave, int qnt, No* filhoEsquerdo, No* filhoDireito){
    No* no = (No*) malloc(sizeof(No));
    no->chave = chave;
    no->qnt = qnt;
    no->filhoEsquerdo = filhoEsquerdo;
    no->filhoDireito = filhoDireito;
    return no;
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim))
        result.push_back (item);
    return result;
}

void countChar(dict &dic, char caracter){
    // dict m;
    // while(*pText != '\0'){
        if (dic[caracter]) dic[caracter] += 1;
        else dic[caracter] = 1;
        // pText++;
    // }
    // return m;
}

dict readFile(string path){
    string text;
    char caracter;
    dict dic;
    ifstream myfile (path); 
    // if (myfile.is_open()){
        while (myfile >> noskipws >> caracter){ 
            // text += caracter;
            countChar(dic, caracter);
        }
        myfile.close();
        // cout << text;
        // return text;
        return dic;
    // } else cout << "Unable to open file";
    // myfile.close();
    // return nullptr;
}

No* codificaoHuffman(Heap heap){
    No* left;
    No* right;
    No sum;

    while(heap.heapSize != 1){
        left = heap.extractMinimum();
        right = heap.extractMinimum();
        sum.chave = internNode;
        sum.qnt = left->qnt + right->qnt;
        sum.filhoEsquerdo = left;
        sum.filhoDireito = right;
        heap.insert(sum);
    }
    return heap.extractMinimum();
}

tabelaSimbolos gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr) tabela[no->chave] = codigo;
    else {
        tabela = gerarTabelaCodificacao(no->filhoEsquerdo, codigo + "0", tabela);
        tabela = gerarTabelaCodificacao(no->filhoDireito, codigo + "1", tabela);
    }
    return tabela;
}

void exibirTree(No* root){

    cout << root->chave << " - ";
    if(root->filhoEsquerdo != nullptr){
        exibirTree(root->filhoEsquerdo);
    }

    if(root->filhoDireito != nullptr){
        exibirTree(root->filhoDireito);
    }
}

void codify(string inputFile, tabelaSimbolos tabelaCodigos, ofstream &outfile){
    char caracter; // é o que irá iterar no arquivo (ler o arquivo de caracter em caracter)
    string code; // serve para pegar o código correspondente ao caracter
    int countByte = 0; // um contador para indicar se já foi lido 8 bits, aí se sim eu gravo o byte localizado na var abaixo
    char byteToWrite = 0; // responsável por guardar o byte a ser armazenado no arquivo -> passará por um processo de "apendação" dos codigos relacionados aos caracteres até completar 8 bits
    char extrabits = 0; // serve para informar a quantidade de bits que precisou para preencher o ultimo byte do arquivo

    streamoff extraBitsAddress = outfile.tellp(); // pega a "posicao" da var extrabits no arquivo, pois será necessário modifica-la no final
    outfile.write(&extrabits, sizeof(char));
    ifstream myfile (inputFile); // abertura do arquivo

    if (myfile.is_open()){
        while (myfile >> noskipws >> caracter){ 
            code = tabelaCodigos[caracter];
            for(int i = 0; i < code.length(); i++){
                if(countByte == 8){
                    if(myfile.eof()) break;
                    outfile.write((char*)&byteToWrite, sizeof(char));
                    countByte = 0;
                    byteToWrite = 0;
                }  
                // processo de apendação de bits no byteToWrite
                byteToWrite = byteToWrite << 1; 
                if(code[i] == '1') byteToWrite = byteToWrite | (char) 1;
                countByte++;
            }
        }

        if(countByte != 0){ // processo de ver a qnt de bits extras e armazenas na posicao pegada la em cima
            extrabits = (char) bytes - countByte; // simboliza o tanto de bits que falta escrever pra completar 1 byte
            cout << "EXTRABITS:" << (int) extrabits << endl;
            byteToWrite = byteToWrite << extrabits; // da um shiftada do tanto de extrabits
            outfile.write((char*)&byteToWrite, sizeof(char));
            outfile.seekp(extraBitsAddress); //atualizando o valor corredo do extrabits no arquivo
            outfile.write(&extrabits, sizeof(char));
        }
        myfile.close();
    }
}

// Percorrer via pré-ordem: Primeiro a esquerda e depois a direita
void writeTree(No* no, vector<char> &tree){
    if(no == nullptr) // nó nulo
        tree.push_back(indicadorNulo);
    else if(isLeaf(no)){ // nó folha
        tree.push_back(indicadorFolha);
        tree.push_back(no->chave);
    } else{
        tree.push_back(internNode); // nó interno
        writeTree(no->filhoEsquerdo, tree);
        writeTree(no->filhoDireito, tree);
    }
}

No* readTree(string tree, int &posicao, No* no){
    char caracter = tree[posicao];
    // cout << caracter << " - ";

    if(caracter == indicadorNulo){
        return no;
    } 
    else if(caracter == indicadorFolha){
        posicao++;
        caracter = tree[posicao];
        posicao++;
        no = newNo(caracter, 0, nullptr, nullptr);
        return no;
    } 
        no = newNo(internNode, 0, nullptr, nullptr);
        posicao++;
        no->filhoEsquerdo = readTree(tree, posicao, no);
        no->filhoDireito = readTree(tree, posicao, no);
        return no;
}

// arquivo de saida: [num de nos | arvore | qnt de bits | output]
void compress(string inputFile, string outputFile){
    Heap heap;
    // cout << "Lendo arquivo " << inputFile << endl;
    // string texto = readFile(inputFile);
    // char c[texto.size() + 1];
    // strcpy(c, &texto[0]);
    dict countSymbols = readFile(inputFile);
    // dict countSymbols = countChar(c);

    cout << "Gerando Arvore de Huffman..." << endl;
    
    No* no;
    if(countSymbols.empty()) no = nullptr;
    else {
        heap.construir(countSymbols);
        no = codificaoHuffman(heap);
        exibirTree(no);
    }
    
    tabelaSimbolos tabela;
    tabela = gerarTabelaCodificacao(no, "", tabela);
    for(parTabela elem: tabela){
        cout << elem.first << " : " << elem.second << endl;
    }

    cout << "Escrevendo Arvore de Huffman..." << endl;
    ofstream outfile(outputFile, std::ios::binary); 
    vector<char> tree;
    writeTree(no, tree);
    int size = tree.size();
    outfile.write((char*)&size, sizeof(int));
    outfile.write(tree.data(), size);

    cout << "Codificando arquivo..." << endl;
    codify(inputFile, tabela, outfile);

    outfile.close();
    cout << "Done!" << endl;
}

void descompress(string inputFile, string outputFile){
    ifstream myfile (inputFile, std::ios::binary); 
    if (!myfile.is_open()){
        cout << "Error to open file" << endl;
        return;
    }

    int numberNodes;
    myfile.read((char*)&numberNodes, sizeof(int));
    cout << "Numero de nos: " << numberNodes << endl;

    No* no;
    
    string out;
    for(int i = 0; i < numberNodes; ++i){
        char byte;
        myfile.read(&byte, sizeof(char));
        out += byte;
    }

    int pos = 0;
    no = readTree(out, pos, no);
    exibirTree(no);
    No* root = no;
    char extrabits;
    myfile.read(&extrabits, sizeof(char));
    cout << "Quantidade de EXTRABITS: " << (int) extrabits << endl;
    
    ofstream outfile (outputFile, std::ios::binary);
    
    char byteToWrite = 0;
    myfile.read((char*)&byteToWrite, sizeof(char));
    int countBit = 0; // um contador para indicar se já foi lido 8 bits, aí se sim eu gravo o byte localizado na var abaixo
    while(!myfile.eof()){
        int bit = byteToWrite >> (7 - countBit) & (char) 1;
        if(bit == 1) no = no->filhoDireito;
        else no = no->filhoEsquerdo;
        countBit++;
        if(isLeaf(no)){
            outfile.write(&no->chave, sizeof(char));
            no = root;
        } 

        if(countBit == bytes){
            myfile.read((char*)&byteToWrite, sizeof(char));
            countBit = 0;
        }
    }

    cout << "Done!";
    myfile.close();
    outfile.close();
}

int main(int argc,char* argv[]){
    /* if(argc>=2) {
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
    }*/
    // string inputFile = "files/Stavechurch-heddal.bmp";
    string inputFile = "files/ch05-patterns.pdf";
    // string inputFile = "files/teste.txt";
    // string inputFile = "files/books.txt";
    // string inputFile = "files/Stavechurch-heddal.bmp";
    string outputFile = "files/teste.huf";
    // string outputFile2 = "files/img.bmp";
    string outputFile2 = "files/pdfDescompress.pdf";
    // string outputFile2 = "files/testeDescomp.txt";
    // string outputFile2 = "files/bookseDescomp.txt";
    // string outputFile2 = "files/img.bmp";
    compress(inputFile, outputFile);
    descompress(outputFile, outputFile2);
    return 0;
}
