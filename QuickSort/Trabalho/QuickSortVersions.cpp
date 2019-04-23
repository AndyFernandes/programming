// By Andreza Fernandes de Oliveira, april/2019

#include "QuickSortVersions.h"
#include "Funcoes.cpp"
#include <tuple>
#include <time.h>
#include <random>
#include <iostream>
using namespace std;

Funcoes func;

void QuickSortVersions::QuickSortMemoria(int *inicio, int *fim){
    while(inicio < fim){
        int *pivo = func.escolher_pivo2(inicio, fim);
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
        int pivo = func.escolher_pivo_indice(inicio, fim);
        pivo = func.Particao_Lomuto(vetor, inicio, pivo, fim);
        if(pivo > inicio)
            QuickSortIndice(vetor, inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSortIndice(vetor, pivo+1, fim); // chamada a direita
    }
}

void QuickSortVersions::QuickSortAleatorio(int *inicio, int *fim){
    if(inicio < fim) {
        int* pivo = func.escolher_pivo_aleatorio(inicio, fim);
        pivo = func.Particao_Lomuto(inicio, pivo, fim);
        if(pivo > inicio)
            QuickSortAleatorio(inicio, pivo-1);
        
        if(pivo < fim)
            QuickSortAleatorio(pivo+1, fim); 
    }
}

void QuickSortVersions::QuickSortLomuto(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = func.escolher_pivo2(inicio, fim);
        pivo = func.Particao_Lomuto(inicio, pivo, fim);
        if(pivo > inicio)
            QuickSortLomuto(inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSortLomuto(pivo+1, fim); // chamada a direita
    }
}

void QuickSortVersions::QuickSortTriplo(int *inicio, int *fim){
     if(inicio < fim){
        int *pivo = func.escolher_pivo2(inicio, fim);
        tuple <int*, int*> ponteiros = func.Particao_Tripla(inicio, fim, pivo);

        if(get<0>(ponteiros) > inicio)
            QuickSortTriplo(inicio, get<0>(ponteiros)-1);

        if(get<1>(ponteiros) < fim)
            QuickSortTriplo(get<1>(ponteiros)+1, fim);
    }
}

void QuickSortVersions::QuickSortHoare(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = func.escolher_pivo2(inicio, fim);
        func.Selecao_Hoare(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSortHoare(inicio, pivo-1);
        
        if (pivo < fim)
            QuickSortHoare(pivo+1, fim);
    }
}

void QuickSortVersions::QuickSortBFPRT(int *inicio, int *fim){
    if(inicio < fim) {
        int *pivo = func.escolher_pivo2(inicio, fim);
        func.BFPRT(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSortBFPRT(inicio, pivo-1); 

        if(pivo < fim)
            QuickSortBFPRT(pivo+1, fim);
    }
}