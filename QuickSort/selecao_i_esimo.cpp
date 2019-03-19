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

void selecao_i_esimo(int *inicio, int *fim, int *i){
    if(inicio < fim) {
        int *pivo = particao_lomuto(inicio, fim, fim);
        if(i < pivo)
            selecao_i_esimo(inicio, pivo-1, i); // chamada a esquerda
        
        if(i > pivo)
            selecao_i_esimo(pivo+1, fim, i); // chamada a direita
    }
}

int main(){
    int tamanho = 9;
    int vetor[] = {3, 11, 12, 5, 4, 3, 1, 2, 0};
    int *i_esimo = vetor + 2;

    selecao_i_esimo(vetor, vetor + tamanho - 1, i_esimo);
    cout << "I-ésimo: " << *i_esimo << endl;
    print_vector(vetor, vetor+tamanho);

    return 0;
}