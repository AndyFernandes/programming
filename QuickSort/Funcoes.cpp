#include <iostream>
#include <tuple>
#include "Funcoes.h"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;


void Funcoes::print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

void Funcoes::trocar(int* posicao1, int *posicao2){
  int aux = *posicao1;
  *posicao1 = *posicao2;
  *posicao2 = aux;
}

int* Funcoes::copy_vector(int vetor[], int tamanho){
    int* copia = new int[tamanho];
    for(int i = 0; i < tamanho; ++i){
        copia[i] = vetor[i];
    }
    return copia;
}

int Funcoes::Particao_Lomuto(int vetor[], int inicio, int pivo, int fim){
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

int* Funcoes::Particao_Lomuto(int *inicio, int *pivo, int *fim){
    int *m = inicio, *j = inicio + 1, aux = *inicio;
    *inicio = *pivo;
    *pivo = aux;

    for(;j != fim+1; ++j){
       if (*j < *inicio){
            m++;
            aux = *j;
            *j = *m;
            *m = aux; 
       }
    }
    
    aux = *inicio;
    *inicio = *m;
    *m = aux;
    return m;
}

tuple<int*, int*> Funcoes::Particao_Tripla(int *inicio, int *pivo, int *fim){
    int *m = inicio, *i = inicio, *j = inicio + 1, aux;
    trocar(inicio, pivo);

    for(;j != fim+1; ++j){
       if (*j < *inicio){
            i++;
            trocar(i, j); 
            m++;
            trocar(m, i);
       } else if(*j == *inicio ){
            i++;
            trocar(i, j); 
       }
    }
    
    trocar(m, inicio);
    return make_tuple(m, i);   
}

void Funcoes::Selecao_Hoare(int *inicio, int *fim, int *i){
    if(inicio < fim) {
        int *pivo = escolher_pivo2(inicio, fim);
        pivo = Particao_Lomuto(inicio, pivo, fim);
        if(i < pivo)
            Selecao_Hoare(inicio, pivo-1, i); 
        if(i > pivo)
            Selecao_Hoare(pivo+1, fim, i);
    }
}