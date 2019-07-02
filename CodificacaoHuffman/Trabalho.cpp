#include <iostream>
#include "Heap.cpp"
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <time.h>
#include <chrono>
using namespace std;

#define bytes 8
#define internNode '%' // indica nó interno
#define indicadorNulo '#' // indica nó nulo
#define indicadorFolha '$' // indica nó folha

void printNo(No* no, int size){
    for(No* i = no; i != no+size; i ++)
        cout << i->chave << " : " << i->qnt << endl;
}

// Verifica se um nó é folha
bool isLeaf(No* no){
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr) return true;
    return false;
}

// Cria um novo nó
// No* newNo(char chave, int qnt, No* filhoEsquerdo, No* filhoDireito){
//     No* no = (No*) malloc(sizeof(No));
//     no->chave = chave;
//     no->qnt = qnt;
//     no->filhoEsquerdo = filhoEsquerdo;
//     no->filhoDireito = filhoDireito;
//     return no;
// }

// Conta ocorrências de caracteres e armazena-os em um dicionário no estilo 'caracter': numero_ocorencias
void countChar(dict &dic, char caracter){
    if (dic[caracter]) dic[caracter] += 1;
    else dic[caracter] = 1;
}

// Ler um arquivo
// Função utilizada na Compreensão
// Por motivos de tamanho de arquivo e etc tive que ler de caracter em caracter e ir chamando a função acima
dict readFile(string path){
    char caracter;
    dict dic;
    ifstream myfile(path, std::ios::binary);
    while (myfile >> noskipws >> caracter){
        if(myfile.eof()) break;
        // cout << caracter;
        countChar(dic, caracter);
    }
    myfile.close();
    return dic;
}

// Cria a Árvore de Huffman, seguindo as propriedades de Heap
No* codificaoHuffman(Heap heap){
    No* left;
    No* right;
    No* sum;

    while(heap.heapSize != 1){
        left = heap.extractMinimum();
        right = heap.extractMinimum();
        // cout << "Left: " << left->chave << " : " << left->qnt << endl;
        // cout << "Right: " << right->chave << " : " << right->qnt << endl;
        sum = newNo(internNode, left->qnt + right->qnt, left, right);
        // (No*) malloc(sizeof(No));
        // sum->chave = internNode;
        // sum->qnt = left->qnt + right->qnt;
        // sum->filhoEsquerdo = left;
        // sum->filhoDireito = right;
        // cout << "SUM: " << sum->chave << " : " << sum->qnt << endl;
        // cout << "--------------------------" << endl;
        heap.insert(sum);
    }
    return heap.extractMinimum();
}

// Através da Árvore de Huffman, para cada caracter obtemos o seu código e armazenados em um dicionário para facilitar a codificação
tabelaSimbolos gerarTabelaCodificacao(No* no, string codigo, tabelaSimbolos tabela){
    if(!no) return tabela;
    if(no->filhoDireito == nullptr && no->filhoEsquerdo == nullptr) tabela[no->chave] = codigo;
    else {
        tabela = gerarTabelaCodificacao(no->filhoEsquerdo, codigo + '0', tabela);
        tabela = gerarTabelaCodificacao(no->filhoDireito, codigo + '1', tabela);
    }
    return tabela;
}

// Função para printar a Árvore de Huffman -> usada para debbugar
void exibirTree(No* root){

    cout << root->chave << " - ";
    if(root->filhoEsquerdo != nullptr){
        exibirTree(root->filhoEsquerdo);
    }

    if(root->filhoDireito != nullptr){
        exibirTree(root->filhoDireito);
    }
}

// Função para escrever a Árvore de Huffman em um vector. Utilizada na compreensão
// Percorrer via pós-ordem: Primeiro a esquerda e depois a direita
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

// Função para ler a Árvore de Huffman
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

// Função responsável por codificar o arquivo usando o dicionário gerado na função gerarTabelaCodificacao
// Além disso, essa função armazena no arquivo a quantidade de bits usados para completar o último byt (se necessário)
void codify(string inputFile, tabelaSimbolos tabelaCodigos, ofstream &outfile){
    char caracter; // é o que irá iterar no arquivo (ler o arquivo de caracter em caracter)
    string code; // serve para pegar o código correspondente ao caracter
    int countByte = 0; // um contador para indicar se já foi lido 8 bits, aí se sim eu gravo o byte localizado na var abaixo
    char byteToWrite = 0; // responsável por guardar o byte a ser armazenado no arquivo -> passará por um processo de "apendação" dos codigos relacionados aos caracteres até completar 8 bits
    char extrabits = 0; // serve para informar a quantidade de bits que precisou para preencher o ultimo byte do arquivo
    int numBytes = 0; // serve para informar o número de bytes gravados no arquivo
    streamoff extraBitsAddress = outfile.tellp(); // pega a "posicao" da var extrabits no arquivo, pois será necessário modifica-la no final
    outfile.write(&extrabits, sizeof(char));
    streamoff numBytesAddress = outfile.tellp(); // pega a "posicao" da var numBytes no arquivo, pois será necessário modifica-la no final
    outfile.write((char*)&numBytes, sizeof(int));

    ifstream myfile (inputFile, std::ios::binary); // abertura do arquivo

    if (myfile.is_open()){
        while (myfile >> noskipws >> caracter){ 
            code = tabelaCodigos[caracter];
            for(int i = 0; i < code.length(); i++){
                if(countByte == 8){
                    if(myfile.eof()) break;
                    outfile.write(&byteToWrite, sizeof(char));
                    countByte = 0;
                    byteToWrite = 0;
                    numBytes++;
                }  
                // processo de apendação de bits no byteToWrite
                byteToWrite = byteToWrite << 1; 
                if(code[i] == '1') byteToWrite = byteToWrite | (char) 1;
                countByte++;
            }
        }

        if(countByte != 8){ // processo de ver a qnt de bits extras e armazenas na posicao pegada la em cima
            extrabits = (char) bytes - countByte; // simboliza o tanto de bits que falta escrever pra completar 1 byte
            numBytes++; // o ultimo byte vai ser o completado
            cout << "Quantidade de bits extras utilizados: " << (int) extrabits << endl;
            cout << "Quantidade de Bytes gravados: " << numBytes << endl;
            byteToWrite = byteToWrite << extrabits; // da um shiftada do tanto de extrabits
            outfile.write((char*)&byteToWrite, sizeof(char));
            outfile.seekp(extraBitsAddress); //atualizando o valor correto do extrabits no arquivo
            outfile.write(&extrabits, sizeof(char));
            outfile.seekp(numBytesAddress); //atualizando o valor correto da var numBytes no arquivo
            outfile.write((char*)&numBytes, sizeof(int));
        }
        myfile.close();
    }
}

// Função responsável pela compressão do arquivo
// arquivo de saida: [num de nos | arvore | qnt de bits extra | output]
// caso arquivo lido seja vazio: só sai e gera o arquivo .huf vazio
void compress(string inputFile, string outputFile){
    Heap heap;
    // cout << "Lendo arquivo " << inputFile << endl;
    // string texto = readFile(inputFile);
    // char c[texto.size() + 1];
    // strcpy(c, &texto[0]);
    ifstream myfile(inputFile, std::ios::binary);
    if (!myfile.is_open()){
        cout << "Error to open file" << endl;
        return;
    }
    myfile.close();

    cout << "Contagem de ocorrencias de caracteres..." << endl;
    dict countSymbols = readFile(inputFile);
    // dict countSymbols = countChar(c);
    // for(par elem: countSymbols){
    //     cout << elem.first << " : " << elem.second << endl;
    // }

    cout << "Gerando Arvore de Huffman..." << endl;
    No* no;
    if(countSymbols.empty()){
        ofstream outfile(outputFile, std::ios::binary);
        outfile.close();
        cout << "Done!" << endl;
        return;
    }
    heap.construir(countSymbols);
    no = codificaoHuffman(heap);
    // exibirTree(no);
    
    tabelaSimbolos tabela;
    tabela = gerarTabelaCodificacao(no, "", tabela);
    for(parTabela elem: tabela){
        cout << elem.first << " : " << elem.second << endl;
    }

    cout << "Escrevendo Arvore de Huffman..." << endl;
    ofstream outfile;
    outfile.open(outputFile, std::ios::binary); 
    vector<char> tree;
    writeTree(no, tree);
    int size = tree.size();
    outfile.write((char*)&size, sizeof(int));
    outfile.write(tree.data(), size);

    cout << "Codificando arquivo..." << endl;
    codify(inputFile, tabela, outfile);

    outfile.close();
    cout << "Compressao realizada com sucesso!" << endl;
}

// Função responsável por realizar a descompressão do arquivo
// caso o arquivo lido seja vazio: só sai e gera o arquivo .txt vazio
void descompress(string inputFile, string outputFile){
    ifstream myfile (inputFile, std::ios::binary); 
    if (!myfile.is_open()){
        cout << "Error to open file" << endl;
        return;
    } 
    if(myfile.peek() == std::ifstream::traits_type::eof()){
        ofstream outfile (outputFile, std::ios::binary);
        outfile.close();
        myfile.close();
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
    // exibirTree(no);
    No* root = no;
    char extrabits;
    int numBytes;
    
    myfile.read(&extrabits, sizeof(char));
    cout << "Quantidade de EXTRABITS: " << (int) extrabits << endl;
    myfile.read((char*)&numBytes, sizeof(int));
    cout << "Quantidade de Bytes: " << numBytes << endl;
    
    ofstream outfile (outputFile, std::ios::binary);
    
    char byteToWrite = 0;
    myfile.read((char*)&byteToWrite, sizeof(char));
    
    int countBit = 0; // um contador para indicar se já foi lido 8 bits, aí se sim eu gravo o byte localizado na var abaixo
    long iterarBits = 0;
    long totalBits = ((numBytes-1)* bytes) + extrabits;
    // cout << "Total de bits" << totalBits << endl;
    while(!myfile.eof() && iterarBits < totalBits){
        int bit = byteToWrite >> (7 - countBit) & (char) 1;
        
        if(bit == 1) no = no->filhoDireito;
        else no = no->filhoEsquerdo;
        
        countBit++;
        iterarBits++;
        if(isLeaf(no)){
            outfile.write(&no->chave, sizeof(char));
            no = root;
        } 

        if(countBit == bytes){
            myfile.read((char*)&byteToWrite, sizeof(char));
            countBit = 0;
        }
    }
    // cout << "Iterar bits " << iterarBits << endl;

    cout << "Descompressao realiza com sucesso!";
    myfile.close();
    outfile.close();
}

int main(int argc,char* argv[]){
    if(argc>=2) {
       string modo = argv[1];
       string inputFile = argv[2];
       string outputFile = argv[3]; 

       cout << "MODO: " << modo << endl;
       cout << "InputFile: " << inputFile << endl;
       cout << "OutputFile: " << outputFile << endl << endl;

       if(modo == "--compress"){
            auto start = std::chrono::high_resolution_clock::now();
            compress(inputFile, outputFile);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            cout << "Tempo levado para comprimir arquivo: " << duration.count() << " ms" << endl;
       } else if (modo == "--descompress"){
           auto start = std::chrono::high_resolution_clock::now();
           descompress(inputFile, outputFile);
           auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            cout << "Tempo levado para descomprimir arquivo: " << duration.count() << " ms" << endl;
       } else {
           cout << "Comando nao detectado, por favor, tente novamente." << endl;
       }
            
    }
    //string inputFile = "files/Stavechurch-heddal.bmp";
    // string inputFile = "files/ch05-patterns.pdf";
    // string inputFile = "files/teste.txt";
    // string inputFile = "files/books.txt";
    // string inputFile = "files/Stavechurch-heddal.bmp";
    //string outputFile = "files/teste.huf";
    // string outputFile2 = "files/img.bmp";
    // string outputFile2 = "files/pdfDescompress.pdf";
    // string outputFile2 = "files/testeDescomp.txt";
    // string outputFile2 = "files/bookseDescomp.txt";
    //string outputFile2 = "files/img.bmp";
    //compress(inputFile, outputFile);
    //descompress(outputFile, outputFile2);
    return 0;
}
