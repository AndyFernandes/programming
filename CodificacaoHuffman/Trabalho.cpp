#include <iostream>
#include <map>
#include "Heap.cpp"
#include <set>
#include <algorithm>
#include <functional>
using namespace std;
typedef map<char, int> dict;
typedef pair<char, int> par;
// typedef function<bool(dict, dict)> comparator;

/*void print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}*/

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


void codificaoHuffman(){
    No* no = (No*)malloc(sizeof(No));
    //return no;
}

void printNo(No* no, int size){
    for(No* i = no; i != no+size; i ++){
        cout << i->chave << " : " << i->qnt << endl;
    }
}
/* 
LÓGICA:
    1. Primeiro construir um dicionário que conta a ocorrencia de cada caractere
    2. Depois construir uma heap, repassando o dicionário 
        -> Ajeitar minha heap para suportar a estrutura de nós -> sempre ordenará olhando pela quantidade
    
    3. Algoritmo de Huffman

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
    char c[] = "batatinha quando nasce esparrama pelo chao";
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
    cout << "\n\n" << no[1].qnt;

    
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

    // TODO FAZER UMA STRUCT
    return 0;
}