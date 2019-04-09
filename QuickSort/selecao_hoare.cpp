// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

int* Particao_Lomuto(int *inicio, int *pivo, int *fim){
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

void Selecao_Hoare(int *inicio, int *fim, int *i){
    if(inicio < fim) {
        int *pivo = Particao_Lomuto(inicio, fim, fim);
        if(i < pivo)
            Selecao_Hoare(inicio, pivo-1, i); // chamada a esquerda
        if(i > pivo)
            Selecao_Hoare(pivo+1, fim, i); // chamada a direita
    }
}

void QuickSort_Hoare(int *inicio, int *pivo, int *fim){
    if(inicio < fim) {
        Selecao_Hoare(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSort_Hoare(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if (pivo < fim)
            QuickSort_Hoare(pivo+1, fim, fim); // chamada a direita
        
    }
}

int main(){
    int tamanho = 10;
    int vetor[] = {1, -1, 4, 3, 0, 2, 5, 50, 6, 7};
    int posicao = 5;
    int *i_esimo = vetor + posicao;

    //Selecao_Hoare(vetor, vetor + tamanho, i_esimo);
    //cout << posicao + 1 << "o elemento: " << *i_esimo << endl;
   
    QuickSort_Hoare(vetor, i_esimo, vetor + tamanho);
    print_vector(vetor, vetor+tamanho);

    return 0;
}