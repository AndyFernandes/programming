#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n-------------------------------------\n";
}

int* particao_lomuto(int *inicio, int *pivo, int *fim){
    /*
        1A PARTE:   J inicializa na posição inicio + 1, m inicializa na posição inicio.
        2A PARTE:   A partir da posição inicio + 1(j) compara se o elemento na posição j <= pivo (está na posicao inicio)
                    se for <=, troca o maior numero do m (da partição dos menores) pelo o da posição atualmente apontada
                    e incremento +1 em m e j.
        3A PARTE:   No final eu destroca a posicao do inicio <-> pivo (que é agora o m).
    */
   
    int *m = inicio, *j = inicio + 1, aux = *inicio;
    // troca das posições inicio <-> pivo
    *inicio = *pivo;
    *pivo = aux;

    for(;j != fim; ++j){
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

void QuickSort(int *inicio, int *pivo, int *fim){
    /*
        1. particiono o vetor de acordo com o pivo
        2. pra cada metade eu ordeno recursivamento
        PIVO; Sempre será escolhido o último elemento da partição passada
        CASOS PROBLEMÁTICOS:    1. O inicio & pivo ser maior que o fim no caso da chamada a direita
                                2. O pivo & fim ser menor que o inicio no caso da chamada a esquerda
    */

    if(inicio < fim) {
        int *pivo = particao_lomuto(inicio, fim, fim);
        if(pivo > inicio)
            QuickSort(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort(pivo+1, fim, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 9;
    int vetor[] = {7, 11, 12, 5, 4, 3, 1, 2, 0};

    //////////////////////////////////////////////////////////////////////
    // int *new_pivo = particao_lomuto(vetor, vetor + 3, vetor + tamanho);
    // cout << "PIVO:" << *new_pivo << "\n";
    //////////////////////////////////////////////////////////////////////

    QuickSort(vetor, vetor + 4, vetor + tamanho - 1);
    print_vector(vetor, vetor+tamanho);

    return 0;
}