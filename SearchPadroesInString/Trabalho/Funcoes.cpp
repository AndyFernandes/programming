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

void Funcoes::check(int* saida1, int* saida2, int tamanho){
    bool deuRuim = false;
    for(int* i = saida1; i != saida1 + tamanho; ++i){
        if (*i != *saida2){
            deuRuim = true;
            break;
        }
        ++saida2;
    }
    if(deuRuim) cout << "\nSAIDAS DIFERENTES";
    else cout << "\nSAIDAS IGUAIS";
}

void Funcoes::CalculatePi(){}
void Funcoes::KnuthMorrisPratt(const char *texto, const char *padrao, int *saida){}
void Funcoes::ForcaBruta(const char *texto, const char *padrao, int *saida){}

//TODO ajeitar isso aqui
void Funcoes::InstanciaAleatoria(int n, int m, const char *texto, const char *padrao){
    static char c = 'a' + rand()%26;
}

void Funcoes::PiorCaso1(int n, int m, const char *texto, const char *padrao){
    for(int i = 0; i < n; i++){
        //*texto = 'a';
        //++texto;
    }
    for(int i = 0; i < m-1; i++){
        //*padrao = 'a';
        //++padrao;
    }
    //*padrao= 'b';
}

void Funcoes::PiorCaso2(int n, int m, const char *texto, const char *padrao){
    for(int i = 0; i < n; i++){
        //*texto = 'a';
        //++texto;
    }
    for(int i = 0; i < m; i++){
        //*padrao = 'a';
        //++padrao;
    }
}