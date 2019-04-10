// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
// #include "instancias_ruins_QuickSort.hpp"
using namespace std;

int escolher_pivo (int primeiro, int ultimo){
  return primeiro + abs((ultimo - primeiro)/2);
}

void print_vector(int vetor[], int tamanho){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(int i = 0; i < tamanho; ++i){
        cout << vetor[i] << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

int Particao_Lomuto(int vetor[], int inicio, int pivo, int fim){
    int m = inicio, j = inicio + 1, aux = vetor[inicio];
    vetor[inicio] = vetor[pivo];
    vetor[pivo] = aux;

    for(;j <= fim; ++j){
       if (vetor[j] < vetor[inicio]){
            ++m;
            aux = vetor[j];
            vetor[j] = vetor[m];
            vetor[m] = aux; 
       }
    }
    
    aux = vetor[inicio];
    vetor[inicio] = vetor[m];
    vetor[m] = aux;

    return m;
}

void QuickSort_Indice(int vetor[], int inicio, int fim){
    if(inicio < fim) {
        int pivo = escolher_pivo(inicio, fim);
        pivo = Particao_Lomuto(vetor, inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_Indice(vetor, inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Indice(vetor, pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 15;
     int vetor[] =  {1, 20, 51, 3, 5, 100, -1, 30, 2, 4, 25, 24, 30, 19, 14};
    
    // int a = escolher_pivo(3, 9);
    QuickSort_Indice(vetor, 0, 14);
    // int m = Particao_Lomuto(vetor, 0, 4, 9);
    // print_vector(vetor, vetor+tamanho);
    // m = Particao_Lomuto(vetor, 0, 2, 9);
    print_vector(vetor, tamanho);

    return 0;
}