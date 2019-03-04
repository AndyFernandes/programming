#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


int* particao_lomuto(int *inicio, int *pivo, int *fim){
    int *m = inicio, *aux = inicio, *aux2 = inicio;
    int cont_m, cont_j;

    // 1a parte: troca das posições inciais <-> pivô
    // j inicializa na posição inicio + 1, m inicializa na posição inicio
    inicio = pivo;
    pivo = aux;

    // 2a parte: A partir da posição inicio + 1, que é o j
    // eu comparo se o elemento na posição j é <= que o pivo (que se encontra na posicao inicio)
    // Se for <=, troca o maior numero do m (da partição dos menores) pelo o da posição atualmente apontada
    // e incremento +1
    // AJEITAR ESSA PARTE
    for(int *j = aux + 1; j != fim+1; ++j){
       if (*j <= *inicio){
           cout << "J: " << *j << " | inicio: " << *inicio << "\n";
           aux2 = m;
           m = j;
           j = m;
           m++;
       }
    }

    // 3a parte: no final eu destroco a posicao do inicio <-> pivo
    aux2 = inicio;
    inicio = pivo;
    pivo = aux2;

    return pivo;
}

int main(){
    int vetor[6] = {8,8,4,8,6,7};
    int *new_pivo = particao_lomuto(vetor, vetor + 3, vetor + 5);
    return 0;
}