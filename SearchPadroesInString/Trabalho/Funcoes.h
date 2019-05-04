// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
using namespace std;

class Funcoes {
    public:
        void print_vector(int *inicio, int *fim);
        void check(int* saida1, int* saida2, int tamanho);
        void CalculatePi(const char *padrao, int *pi);
        void KnuthMorrisPratt(const char *texto, const char *padrao, int *saida);
        void ForcaBruta(const char *texto, const char *padrao, int *saida);
        char* InstanciaAleatoria(int n);
        char* PiorCaso1(int n);
        char* PiorCaso1Padrao(int n);
        char* PiorCaso2(int n);
        void completeZeros(int* vetor, int tamanho);
};