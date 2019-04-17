// By Andreza Fernandes de Oliveira, april/2019
// FALTA TERMINAR
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

int* Particao_Lomuto(int *inicio, int *pivo, int *fim){
    int *m = inicio, *j = inicio + 1, aux = *inicio;
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

// TA BUGADO
void QuickSort_logn(int *inicio, int *fim){
    while(inicio < fim){
        // func escolher pivo
        int *pivo = Particao_Lomuto(inicio, fim, fim);
        int tamEsquerda = pivo - inicio;
        int tamDireita = fim - pivo;
        if(tamEsquerda > tamDireita){
            // recursivo para direita e interativo para esquerda
            if(pivo < fim)
                QuickSort_logn(pivo+1, fim);
            fim = pivo - 1;
        } else {
            // recursivo para esquerda e interativo para direita
            if(pivo > inicio)
                QuickSort_logn(inicio, pivo-1);
            inicio = pivo + 1;
        }
        
        
    }
}

int main(){
    int tamanho = 14;
     int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8, 4, 4, 20, 19, 18};
    
    QuickSort_logn(vetor, vetor + tamanho-1);
    print_vector(vetor, vetor+tamanho);

    return 0;
}