// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;
Funcoes func;

void QuickSortLaco(int *inicio, int *pivo, int *fim){
    while(inicio < fim){
        int *pivo = func.Particao_Lomuto(inicio, fim, fim);
        if(pivo > inicio)
            QuickSortLaco(inicio, pivo-1, pivo-1);
        inicio = pivo + 1;
        pivo = fim;
    }
}

int main(){
    int tamanho = 9;
     int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8};
    int *pivo = vetor + 4; 
    
    QuickSortLaco(vetor, vetor + 4, vetor + tamanho - 1);
    func.print_vector(vetor, vetor+tamanho);
    return 0;
}