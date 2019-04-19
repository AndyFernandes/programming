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

int* Funcoes::vetor_aleatorio(int tamanho, int valor_inicial, int valor_final){
    int *vetor = new int[tamanho];
    
    for(int *i = vetor; i != vetor + tamanho; ++i){
        *i = valor_inicial + (rand() % valor_final);
    }
    return vetor;
}

void Funcoes::check(int* inicio, int* fim){
    int achou = 0;
    for(int *i = inicio; i != fim; ++i){
        if(*i > *(i+1)){
            ++achou;
        }
    }
    if(achou == 0)
        cout << "\nVETOR ORDENADO!\n";
    else
        cout << "\nVETOR DESORDENADO!\n";
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

void Funcoes::BFPRT(int* inicio, int* fim, int* pivo){
    int tamanho = fim - inicio;

    if(tamanho <= 5){
        Selecao_Hoare(inicio, fim, pivo);
        return;
    }

    int *init, *meio, *finish;
    int tamanho_vetor_ponteiros = (tamanho/5) + 1;

    for(int i = 0; i < tamanho_vetor_ponteiros; ++i){
        init = inicio + i*5;
        if(i == tamanho_vetor_ponteiros - 1){
            finish = init + ((fim-1) - init);
            meio = init + ((finish - init)/2);
        } else {
            meio = init + 2;
            finish = init + 4;
        }

        Selecao_Hoare(init, finish, meio);
        trocar(meio, inicio+i);
    }

    init = inicio;
    finish = inicio + tamanho_vetor_ponteiros - 1;
    meio = init + ((finish - init)/2);
    BFPRT(init, finish, meio);

     tuple<int*, int*> ponteiros = Particao_Tripla(inicio, pivo, fim);
     if (pivo < get<0>(ponteiros)){
         BFPRT(inicio, get<0>(ponteiros)-1, pivo);
     } else if (pivo > get<1>(ponteiros)) {
         BFPRT(get<1>(ponteiros)+1, fim, pivo);
     } else {
         pivo = get<0>(ponteiros);
     }
}