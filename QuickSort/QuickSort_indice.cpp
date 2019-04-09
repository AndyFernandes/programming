// By Andreza Fernandes de Oliveira, april/2019
// FALTA TERMINAR
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
// #include "instancias_ruins_QuickSort.hpp"
using namespace std;

int escolher_pivo (int primeiro, int ultimo){
  return primeiro + abs((ultimo - primeiro)/2);
}

void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

int Particao_Lomuto(int vetor[], int inicio, int pivo, int fim){
    int m = inicio, j = inicio + 1, aux = inicio;
    inicio = pivo;
    pivo = aux;

    for(;j != fim+1; ++j){
       if (j < inicio){
            ++m;
            aux = j;
            j = m;
            m = aux; 
       }
    }
    
    aux = inicio;
    inicio = m;
    m = aux;

    return m;
}

void QuickSort_Indice(int vetor[], int inicio, int fim){
    if(inicio < fim) {
        int pivo = escolher_pivo(inicio, fim);
        pivo = Particao_Lomuto(vetor, inicio, fim, pivo);
        if(pivo > inicio)
            QuickSort_Indice(vetor, inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Indice(vetor, pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 10;
     int vetor[] =  {1, 20, 51, 3, 5, 100, -1, 30, 2, 4};
    int *pivo = vetor + 4; 
    
    QuickSort_Indice(vetor, 0, 9);
    cout << "PIVÔ: " << *pivo << endl;
    print_vector(vetor, vetor+tamanho);

    return 0;
}