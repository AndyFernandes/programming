// By Andreza Fernandes de Oliveira, april/2019
// FALTA TERMINAR
#include "QuickSort_Versions.h"
#include "instancias_ruins_QuickSort.hpp"
#include <iostream>
#include <random>
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

int* vetor_aleatorio(){
    random_device rd;
    mt19937 ger(rd());
    uniform_int_distribution<int> dis(1, 6);
    
    int meu_num = dis(ger);
    cout << meu_num;
    return;
}

void menu(){
    int tamanho;
    
    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    int* vetor = veto
}

int main(){
  menu();
  return 0;
}