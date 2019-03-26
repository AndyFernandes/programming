#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<tuple> // for tuple 
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

void trocar(int* posicao1, int *posicao2){
  int aux = *posicao1;
  *posicao1 = *posicao2;
  *posicao2 = aux;
}

int* Particao_Lomuto(int *inicio, int *pivo, int *fim){
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

tuple<int*, int*> Particao_Tripla(int *inicio, int *pivo, int *fim){
    /*
        1A PARTE:   J inicializa na posição inicio + 1, m&i inicializa na posição inicio.
        2A PARTE:   A partir da posição inicio + 1(j) compara:
                    j < pivo:  incrementa m, guarda o valor de m, m <- j, incrementa i, j <- i, i <- valor de m guardado
                    j = pivo: incrementa i
                    j > pivo: incrementa j
        3A PARTE:   No final eu destroca a posicao do inicio <-> pivo (que é agora o m).
    */
    int *m = inicio, *i = inicio, *j = inicio + 1, aux;
    // troca das posições inicio <-> pivo
    trocar(inicio, pivo);

    for(;j != fim+1; ++j){
       if (*j < *inicio){
            m++;
            aux = *m;
            *m = *j;

            i++;
            *j = *i;
            *i = aux;
       } else if(*j == *inicio ){
            i++;
            trocar(i, j); 
       }
    }
    
    trocar(m, inicio);
    return make_tuple(m, i);   
}

void QuickSort_Lomuto(int *inicio, int *pivo, int *fim){
    /*
        1. particiono o vetor de acordo com o pivo
        2. pra cada metade eu ordeno recursivamento
        PIVO; Sempre será escolhido o último elemento da partição passada
        CASOS PROBLEMÁTICOS:    1. O inicio & pivo ser maior que o fim no caso da chamada a direita
                                2. O pivo & fim ser menor que o inicio no caso da chamada a esquerda
    */

    if(inicio < fim) {
        int *pivo = Particao_Lomuto(inicio, fim, fim);
        if(pivo > inicio)
            QuickSort_Lomuto(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Lomuto(pivo+1, fim, fim); // chamada a direita
    }
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
    int tamanho = 9;
    int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8};
    int *pivo = vetor + 4; 
    
    //QuickSort_lomuto(vetor, vetor + 4, vetor + tamanho - 1);
    //print_vector(vetor, vetor+tamanho);

    cout << "PIVO: " << *pivo << endl;
    print_vector(vetor, vetor+tamanho);
    //QuickSort_tripla(vetor, pivo, vetor + tamanho - 1);
    print_vector(vetor, vetor+tamanho);
    return 0;
}