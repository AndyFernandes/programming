// By Andreza Fernandes de Oliveira, april/2019

#include <random>
#include <iostream>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

int* Particao_Lomuto(int *inicio, int *pivo, int *fim){
    int *m = inicio, *j = inicio + 1, aux = *inicio;
    *inicio = *pivo;
    *pivo = aux;

    for(;j != fim+1; ++j){
       if (*j < *inicio){
            m++;
            aux = *j;
            *j = *m;
            *m = aux; 
       }
    }
    
    aux = *inicio;
    *inicio = *m;
    *m = aux;

    return m;
}

void QuickSort_Aleatorio(int *inicio, int *fim){
    if(inicio < fim) {
        srand(time(nullptr));
        int* pivo = inicio + (rand()%(fim-inicio));
        pivo = Particao_Lomuto(inicio, fim, fim);
        if(pivo > inicio)
            QuickSort_Aleatorio(inicio, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_Aleatorio(pivo+1, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 15;
    int vetor[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    
    QuickSort_Aleatorio(vetor, vetor + tamanho - 1);
    print_vector(vetor, vetor+tamanho);
  return 0;
}