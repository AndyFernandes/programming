// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

Funcoes func;

void QuickSort_Hoare(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = func.escolher_pivo2(inicio, fim);
        func.Selecao_Hoare(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSort_Hoare(inicio, pivo-1);
        
        if (pivo < fim)
            QuickSort_Hoare(pivo+1, fim);
    }
}

int main(){
    int tamanho = 10;
    int vetor[] = {1, -1, 4, 3, 0, 2, 5, 50, 6, 7};
    int posicao = 5;
    int *i_esimo = vetor + posicao;
   
    QuickSort_Hoare(vetor, vetor + tamanho-1);
    func.print_vector(vetor, vetor+tamanho);

    return 0;
}