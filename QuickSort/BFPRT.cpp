// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include "Funcoes.cpp"
#include<tuple> 
using namespace std;

Funcoes func;

/*
      1.  Colete os elementos da matriz em grupos de 5. Se o número de elementos na matriz não for um múltiplo de 5, crie um grupo adicional (que conterá no máximo 4 elementos).
      2.  Encontre a mediana de cada grupo.
      2.a. Jogue as medianas pro inicio do vetor trocando os lugares com os demais elementos
      3.  Por meio de uma chamada recursiva, encontre a mediana das medianas.
      4.  Use a mediana das M medianas como um pivô da seleção de hoare
      //e chame o algoritmo recursivamente na matriz apropriada, exatamente como no algoritmo quickselect .
*/
void BFPRT(int* inicio, int* fim, int* pivo){
    int tamanho = abs(fim - inicio) + 1;

    if(tamanho <= 5){
        func.Selecao_Hoare(inicio, fim, pivo);
        return;
    }

    int *init, *meio, *finish;
    int tamanho_vetor_ponteiros = abs(tamanho/5) + 1;

    for(int i = 0; i < tamanho_vetor_ponteiros; ++i){
        init = inicio + i*5;
        if(i == tamanho_vetor_ponteiros - 1){
            finish = init + ((fim-1) - init); //obs
            meio = init + abs((finish - init)/2);
        } else {
            meio = init + 2;
            finish = init + 4;
        }

        func.Selecao_Hoare(init, finish, meio);
        func.trocar(meio, inicio+i);
    }

    // 3o passo: Selecionar o elemento do meio (na sua posicao correta se tivesse ordenado) e retornar ele pro QuickSort
    init = inicio;
    finish = inicio + tamanho_vetor_ponteiros - 1;
    meio = init + abs((finish - init)/2);
    BFPRT(init, finish, meio);

     // 4o passo: Partição tripla e testes
     tuple<int*, int*> ponteiros = func.Particao_Tripla(inicio, pivo, fim);
     if (pivo < get<0>(ponteiros)){
         BFPRT(inicio, get<0>(ponteiros)-1, pivo);
     } else if (pivo > get<1>(ponteiros)) {
         BFPRT(get<1>(ponteiros)+1, fim, pivo);
     } else {
         pivo = get<0>(ponteiros);
     }
}

// DOING
void QuickSort_BFPRT(int *inicio, int *pivo, int *fim){
    if(inicio < fim) {
        BFPRT(inicio, fim, pivo);
        if(pivo > inicio)
            QuickSort_BFPRT(inicio, pivo-1, pivo-1); // chamada a esquerda

        if(pivo < fim)
            QuickSort_BFPRT(pivo+1, fim, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 18;
    int vetor[] = {20, 1, 1, 4, 100, 12, 4, 3, 3, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    // 0, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 12, 20, 100
    int *fim = vetor + tamanho;
    func.print_vector(vetor, vetor + tamanho);
    QuickSort_BFPRT(vetor, vetor + 8, fim-1);
    func.print_vector(vetor, vetor + tamanho);
    return 0;
}