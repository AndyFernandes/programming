#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <tuple>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n-------------------------------------\n";
}
void trocar(int* posicao1, int *posicao2){
  int aux = *posicao1;
  *posicao1 = *posicao2;
  *posicao2 = aux;
}

tuple<int*, int*> Particao_Tripla(int *inicio, int *pivo, int *fim){
    /*
        1A PARTE:   J inicializa na posição inicio + 1, m&i inicializa na posição inicio.
        2A PARTE:   A partir da posição inicio + 1(j) compara:
                    j < pivo:  incrementa m, guarda o valor de m, m <- j, incrementa i, j <- i, i <- valor de m guardado
                    j = pivo: incrementa i
                    j > pivo: incrementa j
        3A PARTE:   No final eu destroca a posicao do inicio <-> pivo (que é agora o m).
    */
    int *m = inicio, *i = inicio, *j = inicio + 1, aux;
    // troca das posições inicio <-> pivo
    trocar(inicio, pivo);

    for(;j != fim+1; ++j){
       if (*j < *inicio){
            i++;
            trocar(i, j); 
            m++;
            trocar(m, i);
       } else if(*j == *inicio ){
            i++;
            trocar(i, j); 
       } 
    }
    
    trocar(m, inicio);
    return make_tuple(m-1, i+1);   
}

void QuickSort_Tripla(int *inicio, int *pivo, int *fim){
     if(inicio < fim){
        tuple <int*, int*> ponteiros = Particao_Tripla(inicio, fim, pivo);

        if(get<0>(ponteiros) > inicio){
            QuickSort_Tripla(inicio, get<0>(ponteiros), get<0>(ponteiros));
        }

        if(get<1>(ponteiros) < fim){
            QuickSort_Tripla(get<1>(ponteiros), fim, fim);
        }
    }
}

int main(){
    int tamanho = 15;
    int vetor[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    int *pivo = vetor + 4; 

    cout << "\nPIVO: " << *pivo  << "\n";
    // //Particao_Tripla(vetor, vetor + 3, vetor + tamanho, menores, iguais);
    //tuple <int*, int*> ponteiros = Particao_Tripla(vetor, pivo, vetor + tamanho);
                                  
    //cout << "\nFIM MENORES:\t" << *get<0>(ponteiros) << "\t|\tINICIO MAIORES:\t" << *get<1>(ponteiros) << "\n";
    print_vector(vetor, vetor + tamanho);

    
    QuickSort_Tripla(vetor, pivo, vetor + tamanho-1);
    print_vector(vetor, vetor+tamanho);
    return 0;                   
}