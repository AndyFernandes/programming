#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<tuple> // for tuple 
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
// DOING
void BFPRT(int* inicio, int* fim, int *pivo){
    int tamanho_vetor_ponteiros = abs((fim - inicio)/5) + 1;
    // vou montar um vetor pra pegar os ponteiros pros elementos ou então definir uma struct
    int* medianas[tamanho_vetor_ponteiros];
    // mediana = inicio + 2; fim = inicio + 4
    int *init, *meio, *finish;
    for(int i = 0; i < tamanho_vetor_ponteiros-1; ++i){
        init = inicio + i*5;
        meio = inicio + 2 + i*5;
        finish = inicio + 4 + i*5;
        //cout << "INICIO: " << *init << " | MEIO: " << *meio << " | FIM: " << *finish << endl;
        Selecao_Hoare(init, finish, meio);
        medianas[i] = inicio + 2 + i*5;
    }
    // pegando o ultimo elemento
    init = medianas[tamanho_vetor_ponteiros - 2]+2;
    finish = init + ((fim-1) - init);
    meio = init + abs((finish - init)/2);
    Selecao_Hoare(init, finish, meio);
    medianas[tamanho_vetor_ponteiros - 1] = meio;

    // TODO: tá faltando eu catar a mediana do ultimo segmento
    
    // cout << endl;
    // for(int i = 0; i < tamanho_vetor_ponteiros; i++){
    //       cout << " | " << *medianas[i];
    // }
    // cout << endl;

    // 2o passo: Botar as medianas pras posicoes iniciais do vetor
    for(int i = 0; i < tamanho_vetor_ponteiros; i++){
        trocar(medianas[i], inicio+i);
    }

    // 3o passo: Selecionar o elemento do meio (na suapociao correta se tivesse ordenado) e retornar ele pro QuickSort
    init = medianas[0];
    cout << tamanho_vetor_ponteiros;
    finish = medianas[0] + 2;
    meio = init + abs((finish - init)/2);
    cout << "INICIO: " << *init << " | MEIO: " << *meio << " | FIM: " << *finish << endl;
    //Selecao_Hoare(init, finish, meio);



        

    // teste pra como acessar os ponteiros
    //   cout << *medianas[0] << endl;
    //   cout << *medianas[1] << endl;
    //   cout << *medianas[2] << endl;
      
}

// DOING 
void QuickSort_BFPRT(int *inicio, int *pivo, int *fim){
   if(inicio < fim) {
        BFPRT(inicio, pivo, fim);
        if(pivo > inicio)
            QuickSort_BFPRT(inicio, pivo-1, pivo-1); // chamada a esquerda
        
        if(pivo < fim)
            QuickSort_BFPRT(pivo+1, fim, fim); // chamada a direita
    }
}

int main(){
    int tamanho = 18;
    int vetor[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    int *fim = vetor + tamanho; 
    print_vector(vetor, vetor + tamanho);
    BFPRT(vetor, fim, fim);
    print_vector(vetor, vetor + tamanho);
    return 0;
}