// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

Funcoes func;
void QuickSort_Lomuto(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = escolher_pivo2(inicio, fim);
        pivo = func.Particao_Lomuto(inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_Lomuto(inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Lomuto(pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 10;
     int vetor[] =  {1, 20, 51, 3, 5, 100, -1, 30, 2, 4};
     
    
    QuickSort_Lomuto(vetor, vetor + tamanho-1);
    func.print_vector(vetor, vetor+tamanho);

    return 0;
}