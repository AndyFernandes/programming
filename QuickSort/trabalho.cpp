// #include "QuickSort_versions.h"
#include "instancias_ruins_QuickSort.hpp"
#include <iostream>
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

int main(){
    int tamanho = 15;
    int vetor[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    int *pivo = vetor + 4; 

    // print_vector(vetor, vetor + tamanho);
  return 0;
}