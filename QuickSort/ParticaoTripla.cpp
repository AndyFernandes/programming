// By Andreza Fernandes de Oliveira, april/2019

#include <tuple>
#include <iostream>
#include "Funcoes.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

Funcoes func;

void QuickSort_Tripla(int *inicio, int *fim){
     if(inicio < fim){
        int *pivo = func.escolher_pivo2(inicio, fim);
        tuple <int*, int*> ponteiros = func.Particao_Tripla(inicio, fim, pivo);

        if(get<0>(ponteiros)-1 > inicio)
            QuickSort_Tripla(inicio, get<0>(ponteiros)-1);

        if(get<1>(ponteiros)+1 < fim)
            QuickSort_Tripla(get<1>(ponteiros)+1, fim);
    }
}

int main(){
    int tamanho = 15;
    int vetor[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    int *pivo = func.escolher_pivo2(vetor, vetor+4);

    //cout << "\nPIVO: " << *pivo  << "\n";
    //tuple <int*, int*> ponteiros = func.Particao_Tripla(vetor, pivo, vetor + tamanho);
                                  
    //cout << "\nFIM MENORES:\t" << *get<0>(ponteiros) << "\t|\tINICIO MAIORES:\t" << *get<1>(ponteiros) << "\n";
    func.print_vector(vetor, vetor + tamanho);
    
    QuickSort_Tripla(vetor,  vetor + tamanho-1);
    func.print_vector(vetor, vetor+tamanho);
    return 0;                   
}