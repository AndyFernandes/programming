// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include<tuple> 
using namespace std;

Funcoes func;

void QuickSort_BFPRT(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = func.escolher_pivo2(inicio, fim);
        func.BFPRT(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSort_BFPRT(inicio, pivo-1); // chamada a esquerda

        if(pivo < fim)
            QuickSort_BFPRT(pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 18;
    int vetor[] = {20, 1, 1, 4, 100, 12, 4, 3, 3, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    // 0, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 12, 20, 100
    int *fim = vetor + tamanho;
    func.print_vector(vetor, vetor + tamanho);
    QuickSort_BFPRT(vetor, fim-1);
    func.print_vector(vetor, vetor + tamanho);
    return 0;
}