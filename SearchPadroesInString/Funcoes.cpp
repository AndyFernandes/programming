// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include "Funcoes.h"
using namespace std;

void Funcoes::print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

void Funcoes::CalculatePi(){}
void Funcoes::KnuthMorrisPratt(const char *texto, const char *padrao, int *saida){}
void Funcoes::ForcaBruta(const char *texto, const char *padrao, int *saida){}
void Funcoes::InstanciaAleatoria(int n, int m, const char *texto, const char *padrao){}
void Funcoes::PiorCaso1(int n, int m, const char *texto, const char *padrao){}
void Funcoes::PiorCaso2(int n, int m, const char *texto, const char *padrao){}