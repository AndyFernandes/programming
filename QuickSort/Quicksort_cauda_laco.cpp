#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n-------------------------------------\n";
}

int* Particao_Lomuto(int *inicio, int *pivo, int *fim){
    int *m = inicio, *j = inicio + 1, aux = *inicio;

    *inicio = *pivo;
    *pivo = aux;

    for(;j != fim; ++j){
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

// Ver se tá certo
// se  a troca dos ponteiros é assim mesmo ou é só por conteúdo como a arina sempre diz
void QuickSort_Cauda(int *inicio, int *pivo, int *fim){
    if(inicio < fim) {
        int *pivo = Particao_Lomuto(inicio, fim, fim);
        if(pivo > inicio)
            QuickSort_Cauda(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim){
            int *aux_inicio = pivo+1;
            for(;;){
                if(inicio >= fim)
                    break;
                int *pivo = Particao_Lomuto(inicio, fim, fim);
                if(pivo > inicio)
                    QuickSort_Cauda(inicio, pivo-1, pivo-1);
                aux_inicio = pivo + 1;
                pivo = fim;
            }
        }
    }
}

int main(){
    int tamanho = 9;
     int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8};
    int *pivo = vetor + 4; 
    
    QuickSort_Cauda(vetor, vetor + 4, vetor + tamanho - 1);
    print_vector(vetor, vetor+tamanho);

    return 0;
}