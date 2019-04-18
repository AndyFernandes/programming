// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

Funcoes func;

void QuickSortMemoria(int *inicio, int *fim){
    while(inicio < fim){
        int *pivo = escolher_pivo2(inicio, fim);
        pivo = func.Particao_Lomuto(inicio, pivo, fim);
        
        int tamEsquerda = pivo - inicio;
        int tamDireita = fim - pivo;
        
        if(tamEsquerda > tamDireita){
            // recursivo para direita e interativo para esquerda
            if(pivo < fim)
                QuickSortMemoria(pivo+1, fim);
            fim = pivo - 1;
        } else {
            // recursivo para esquerda e interativo para direita
            if(pivo > inicio)
                QuickSortMemoria(inicio, pivo-1);
            inicio = pivo + 1;
        }  
    }
}

int main(){
    int tamanho = 19;
     int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8, 4, 4, 20, 19, 18, 1,1,0,4,7};
    
    QuickSortMemoria(vetor, vetor + tamanho-1);
    func.print_vector(vetor, vetor+tamanho);

    return 0;
}