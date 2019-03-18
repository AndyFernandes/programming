#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<tuple> // for tuple 
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

void trocar(int* posicao1, int *posicao2){
  int aux = *posicao1;
  *posicao1 = *posicao2;
  *posicao2 = aux;
}

tuple<int*, int*> particao_tripla(int *inicio, int *pivo, int *fim){
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
    //cout << "\n";
    //cout << (int)(pivo - inicio)/2;
    trocar(inicio, pivo);

    for(;j != fim; ++j){
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
       } else {

       }
    }
    
    trocar(m, inicio);
    // duvida se ele aponta pra posicao mesmo ou uma depois
    return make_tuple(m-1, i+1);   
}

// DOING
void QuickSort_cauda_lomuto(int *inicio, int *pivo, int *fim){
    if(inicio < fim) {
        int *pivo = particao_lomuto(inicio, fim, fim);
        if(pivo > inicio)
             QuickSort_cauda_lomuto(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim){
            // AQUI É UM LAÇO P/ METADE DIREITA
        }      
    }
}

// DOING
void QuickSort_cauda_tripla(int *inicio, int *pivo, int *fim){
    if(inicio < fim) {
        int *pivo = particao_lomuto(inicio, fim, fim);
        if(pivo > inicio)
             QuickSort_cauda_lomuto(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim){
            // AQUI É UM LAÇO P/ METADE DIREITA
        }     
    }
}

// DOING
void QuickSort_o_n_with_cauda(int *inicio, int *pivo, int *fim){
    //cout << "\n";
    //cout << (int)(pivo - inicio)/2;
    if(inicio < fim) {
        int *pivo = particao_lomuto(inicio, fim, fim);
        if(pivo > inicio)
             QuickSort_cauda_lomuto(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim){
            // AQUI É UM LAÇO P/ METADE DIREITA
        }  
    }
}

//TODO
int main(){}