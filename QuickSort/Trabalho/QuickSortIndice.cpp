// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include "instancias_ruins_QuickSort.hpp"
#include "QuickSort_Versions.h"
using namespace std;

Funcoes func;

void QuickSort_Indice(int vetor[], int inicio, int fim){
    if(inicio < fim) {
        int pivo = escolher_pivo(inicio, fim);
        pivo = func.Particao_Lomuto(vetor, inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_Indice(vetor, inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Indice(vetor, pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 15;
     int vetor[] =  {1, 20, 51, 3, 5, 100, -1, 30, 2, 4, 25, 24, 30, 19, 14};
    
    QuickSort_Indice(vetor, 0, 14);
    func.print_vector(vetor, vetor+tamanho);

    return 0;
}