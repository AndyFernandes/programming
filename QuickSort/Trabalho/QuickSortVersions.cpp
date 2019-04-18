// By Andreza Fernandes de Oliveira, april/2019

#include "QuickSortVersions.h"
#include "Funcoes.cpp"
#include <tuple>
#include <time.h>
#include <random>
#include <tuple>
using namespace std;

Funcoes func;
void QuickSortVersions::QuickSortMemoria(int *inicio, int *fim){
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

void QuickSortVersions::QuickSortIndice(int vetor[], int inicio, int fim){
    if(inicio < fim) {
        int pivo = escolher_pivo(inicio, fim);
        pivo = func.Particao_Lomuto(vetor, inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_Indice(vetor, inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Indice(vetor, pivo+1, fim); // chamada a direita
    }
}

void QuickSortVersions::QuickSortAleatorio(int *inicio, int *fim){
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

void QuickSortVersions::QuickSortLomuto(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = escolher_pivo2(inicio, fim);
        pivo = func.Particao_Lomuto(inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_Lomuto(inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Lomuto(pivo+1, fim); // chamada a direita
    }
}

void QuickSortVersions::QuickSortTriplo(int *inicio, int *fim){
     if(inicio < fim){
        int *pivo = escolher_pivo2(inicio, fim);
        tuple <int*, int*> ponteiros = func.Particao_Tripla(inicio, fim, pivo);

        if(get<0>(ponteiros)-1 > inicio)
            QuickSort_Tripla(inicio, get<0>(ponteiros)-1);

        if(get<1>(ponteiros)+1 < fim)
            QuickSort_Tripla(get<1>(ponteiros)+1, fim);
    }
}

void QuickSortVersions::QuickSortHoare(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = escolher_pivo2(inicio, fim);
        func.Selecao_Hoare(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSort_Hoare(inicio, pivo-1);
        
        if (pivo < fim)
            QuickSort_Hoare(pivo+1, fim);
    }
}