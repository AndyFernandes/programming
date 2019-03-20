#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<tuple> // for tuple 
using namespace std;

void trocar(int* posicao1, int *posicao2){
  int aux = *posicao1;
  *posicao1 = *posicao2;
  *posicao2 = aux;
}

void print_vector(int *inicio, int *fim){
    cout << "-------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n-------------------------------------\n";
}

/*
      1.  Colete os elementos da matriz em grupos de 5. Se o número de elementos na matriz não for um múltiplo de 5, crie um grupo adicional (que conterá no máximo 4 elementos).
      2.  Encontre a mediana de cada grupo.
      3.  Por meio de uma chamada recursiva, encontre a mediana das medianas.
      4.  Use a mediana das M medianas como um pivô e chame o algoritmo recursivamente na matriz apropriada, exatamente como no algoritmo quickselect .
*/
void BFPRT(int* inicio, int* fim){
  int len = fim - inicio;
  // vou montar um vetor pra pegar os ponteiros pros elementos ou então definir uma struct
  cout << abs(len/5);
}

int main(){
    int tamanho = 18;
    int vetor[] = {7, 0, 12, 5, 5, 3, 1, 2, 8, 4, 7, 0, 12, 5, 5, 3, 1, 2};
    //int *pivo = vetor + 4; 
    BFPRT(vetor, vetor + tamanho);

    print_vector(vetor, vetor + tamanho);
    return 0;
}