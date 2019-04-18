// By Andreza Fernandes de Oliveira, april/2019

#include <random>
#include <iostream>
#include <time.h>
#include "Funcoes.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

Funcoes func;
void QuickSort_Aleatorio(int *inicio, int *fim){
    if(inicio < fim) {
        srand(time(nullptr));
        int* pivo = escolher_pivo_aleatorio(inicio, fim);
        pivo = func.Particao_Lomuto(inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_Aleatorio(inicio, pivo-1);
        
        if(pivo < fim)
            QuickSort_Aleatorio(pivo+1, fim); 
    }
}

int main(){
    int tamanho = 15;
    int vetor[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    
    QuickSort_Aleatorio(vetor, vetor + tamanho - 1);
    func.print_vector(vetor, vetor+tamanho);
  return 0;
}