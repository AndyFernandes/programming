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

// DOING
void QuickSort_logn(int *inicio, int *pivo, int *fim){
    for(;;){
        if(inicio >= fim)
            break;
        int *pivo = Particao_Lomuto(inicio, fim, fim);
        
        if((pivo - inicio) > (fim - pivo)){
            // Lado esquerdo vai pro laço
            // Lado direito recursivo
            QuickSort_logn(pivo+1, fim, fim);
            fim = pivo + 1;
            pivo = pivo + 1;
        } else {
            if(pivo > inicio)
                QuickSort_logn(inicio, pivo-1, pivo-1);
            inicio = pivo + 1;
            pivo = fim;
        }
        
        
    }
}

int main(){
    int tamanho = 9;
     int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8};
    int *pivo = vetor + 4; 
    
    QuickSort_logn(vetor, vetor + 4, vetor + tamanho - 1);
    print_vector(vetor, vetor+tamanho);

    return 0;
}