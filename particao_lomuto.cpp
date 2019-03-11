#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


int* particao_lomuto(int *inicio, int *pivo, int *fim){
    // 1A PARTE: 
    // j inicializa na posição inicio + 1, m inicializa na posição inicio
    int *m = inicio, *j = inicio + 1, aux = *inicio, *v = inicio;
    // troca das posições inicio <-> pivo
    *inicio = *pivo;
    *pivo = aux;

    // 2A PARTE: 
    // a partir da posição inicio + 1(j) compara se o elemento na posição j <= pivo (está na posicao inicio)
    // se for <=, troca o maior numero do m (da partição dos menores) pelo o da posição atualmente apontada
    // e incremento +1 em m e j
    for(;j != fim; ++j){
       if (*j < *inicio){
            m++;
            aux = *j;
            *j = *m;
            *m = aux; 
       }
    }

    // 3A PARTE: 
    // no final eu destroca a posicao do inicio <-> pivo(que é agora o m)
    aux = *inicio;
    *inicio = *m;
    *m = aux;

    return m;
}

int main(){
    int tamanho = 7;
    int vetor[] = {7,5,4,3,1,2,0};
    
    int *new_pivo = particao_lomuto(vetor, vetor + 4, vetor + tamanho);
    cout << "PIVO:" << *new_pivo << "\n";
    
    int *v = vetor;
    cout <<"-------------\n";
    for(int *i = v; i != v + tamanho; i++){
        cout << *i << "-";
    }

    return 0;
}