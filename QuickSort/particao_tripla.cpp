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
void trocar(int* posicao1, int *posicao2){
  int aux = *posicao1;
  *posicao1 = *posicao2;
  *posicao2 = aux;
}

//DOING
void particao_tripla(int *inicio, int *pivo, int *fim, int *fim_menores, int *inicio_maiores){
    /*
        1A PARTE:   J inicializa na posição inicio + 1, m&i inicializa na posição inicio.
        2A PARTE:   A partir da posição inicio + 1(j) compara:
                    j < pivo:  incrementa m, guarda o valor de m, m <- j, incrementa i, j <- i, i <- valor de m guardado
                    j = pivo: incrementa i, troca i com j
                    j > pivo: incrementa j
        3A PARTE:   No final eu destroca a posicao do inicio <-> pivo (que é agora o m).
    */
    int *m = inicio, *i = inicio, *j = inicio + 1, aux;
    // troca das posições inicio <-> pivo
    trocar(inicio, pivo);

    for(;j != fim; ++j){
       if (*j < *inicio){
            m++;
            aux = *m;
            *m = *j;

            i++;
            *j = *i;
            *i = aux;
       } else if(*j == *inicio ){
            i++;
            trocar(i, j); 
       }
    }
    
    // duvida se ele aponta pra posicao mesmo ou uma depois
    fim_menores = m;
    inicio_maiores = i + 1;
}

int main(){
    int tamanho = 9, *inicio, *fim;
    int vetor[] = {7, 11, 12, 5, 5, 3, 1, 2, 0};

    cout << "\nPIVO: " << *(vetor + 3);
    particao_tripla(vetor, vetor + 3, vetor + tamanho, inicio, fim);
    
    cout << "\nFIM MENORES:\t" << *inicio << "\t|\tINICIO MAIORES:\t" << *fim << "\n";
    print_vector(vetor, vetor + tamanho);
    return 0;
}