// By Andreza Fernandes de Oliveira, april/2019

#include <tuple>
#include <iostream>
using namespace std;

class Funcoes {
    public:
        void print_vector(int *inicio, int *fim);
        void trocar(int* posicao1, int *posicao2);
        int* copy_vector(int vetor[], int tamanho);
        void check(int* inicio, int* fim);
        int* vetor_aleatorio(int tamanho, int valor_inicial, int valor_final);
        int Particao_Lomuto(int vetor[], int inicio, int pivo, int fim);
        int* Particao_Lomuto(int *inicio, int *pivo, int *fim);
        tuple<int*, int*> Particao_Tripla(int *inicio, int *pivo, int *fim);
        void Selecao_Hoare(int *inicio, int *fim, int *i);
        void BFPRT(int* inicio, int* fim, int* pivo);
        int* escolher_pivo2(int* primeiro, int* ultimo);
        int* escolher_pivo_aleatorio(int* primeiro, int* ultimo);
};