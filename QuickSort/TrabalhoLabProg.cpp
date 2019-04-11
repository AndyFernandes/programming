// By Andreza Fernandes de Oliveira, april/2019
// FALTA TERMINAR
// #include "QuickSort_Versions.h"
// #include "instancias_ruins_QuickSort.hpp"
#include <iostream>
#include <random>
#include <new>
#include <time.h>
using namespace std;
// Chamar "escrever_instancia(v,n)" sobre o vetor "v" de "n" elementos no qual a instância deve ser escrita.
// Testar se a função retornou "true" (indica erro, falta de memória). Se o retorno for "false", a instância foi construída com sucesso.
// DOING
void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

//TODO: função pra checar se o vetor tá ordenado
void check(int* inicio, int *fim){
}

int* copy_vector(int* inicio, int* fim){
    return inicio;
}

int* vetor_aleatorio(int tamanho, int valor_inicial, int valor_final){
    int *vetor = new int[tamanho];
    srand(time(nullptr));
    for(int *i = vetor; i != vetor + tamanho; ++i){
        *i = valor_inicial + (rand() % valor_final);
    }
    return vetor;
}

void menu(){
    int tamanho;
    int opcao;
    int continuar;
    int* vetor;
    clock_t inicio;
    clock_t total;
    
    
}

int main(){
  


  do {
    menu();
        
        cout << "\n--------------------------------------------------------------------\n";
        cout << "Você deseja continuar? \n1. SIM \n2.NÃO \n:";
        cin >> continuar;
    } while(continuar == 1);
  return 0;
}