#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

int Particao_Lomuto(int vetor[], int inicio, int fim){
    int m = inicio, j = inicio + 1, aux = inicio;
    inicio = pivo;
    pivo = aux;

    for(;j != fim+1; ++j){
       if (j < inicio){
            ++m;
            aux = j;
            j = m;
            m = aux; 
       }
    }
    
    aux = inicio;
    inicio = m;
    m = aux;

    return m;
}

void QuickSort_Lomuto(int vetor[], int inicio, int fim){
    /*
        1. particiono o vetor de acordo com o pivo
        2. pra cada metade eu ordeno recursivamento
        PIVO; Sempre será escolhido o último elemento da partição passada
        CASOS PROBLEMÁTICOS:    1. O inicio & pivo ser maior que o fim no caso da chamada a direita
                                2. O pivo & fim ser menor que o inicio no caso da chamada a esquerda
    */

    if(inicio < fim) {
        int pivo = Particao_Lomuto(vetor, inicio, fim);
        if(pivo > inicio)
            QuickSort_Lomuto(vetor, inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Lomuto(vetor, pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 10;
     int vetor[] =  {1, 20, 51, 3, 5, 100, -1, 30, 2, 4};
    int *pivo = vetor + 4; 
    
    QuickSort_Lomuto(vetor, 0, 9);
    cout << "PIVÔ: " << *pivo << endl;
    print_vector(vetor, vetor+tamanho);

    return 0;
}