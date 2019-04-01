#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <tuple> // for tuple 
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

void Selecao_Hoare(int *inicio, int *fim, int *i){
    if(inicio < fim) {
        int *pivo = Particao_Lomuto(inicio, fim, fim);
        if(i < pivo)
            Selecao_Hoare(inicio, pivo-1, i); // chamada a esquerda
        if(i > pivo)
            Selecao_Hoare(pivo+1, fim, i); // chamada a direita
    }
}
/*
      1.  Colete os elementos da matriz em grupos de 5. Se o número de elementos na matriz não for um múltiplo de 5, crie um grupo adicional (que conterá no máximo 4 elementos).
      2.  Encontre a mediana de cada grupo.
      2.a. Jogue as medianas pro inicio do vetor trocando os lugares com os demais elementos
      3.  Por meio de uma chamada recursiva, encontre a mediana das medianas.
      4.  Use a mediana das M medianas como um pivô da seleção de hoare 
      //e chame o algoritmo recursivamente na matriz apropriada, exatamente como no algoritmo quickselect .
*/
int* BFPRT(int* inicio, int* fim, int *pivo){
    int tamanho_vetor_ponteiros = abs((fim - inicio)/5) + 1;
 
    if(tamanho_vetor_ponteiros <= 5){
        Selecao_Hoare(inicio, fim, inicio + abs((fim - inicio)/2));
        return (inicio + abs((fim - inicio)/2));
    } 

    int *init, *meio, *finish;

    for(int i = 0; i < tamanho_vetor_ponteiros; ++i){
        init = inicio + i*5;
        if(i == tamanho_vetor_ponteiros-1){
            finish = init + ((fim-1) - init);
            meio = init + abs((finish - init)/2);
        } else {
            meio = inicio + 2 + i*5;
            finish = inicio + 4 + i*5;
        }

        Selecao_Hoare(init, finish, meio);
        trocar(meio, inicio+i);
    }
    
    // 3o passo: Selecionar o elemento do meio (na sua posicao correta se tivesse ordenado) e retornar ele pro QuickSort
    init = inicio;
    finish = inicio + tamanho_vetor_ponteiros - 1;
    meio = init + abs((finish - init)/2);
    meio = BFPRT(init, finish, meio); 
    return meio;
}
 
void QuickSort_BFPRT(int *inicio, int *pivo, int *fim){
   if(inicio < fim) {
        int *pivo = BFPRT(inicio, fim, pivo);
        if(pivo > inicio)
           QuickSort_BFPRT(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
           QuickSort_BFPRT(pivo+1, fim, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 18;
    int vetor[] = {20, 1, 1, 4, 100, 12, 4, 3, 3, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int *fim = vetor + tamanho; 
    print_vector(vetor, vetor + tamanho);
    //int * a = BFPRT(vetor, fim, vetor + 6);
    QuickSort_BFPRT(vetor, vetor + 6, fim);
    print_vector(vetor, vetor + tamanho);
    return 0;
}