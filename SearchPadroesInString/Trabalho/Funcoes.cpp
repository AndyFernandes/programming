// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include <string.h>
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
            cout << *i;
            break;
        }
        ++saida2;
    }
    if(deuRuim) cout << "\nSAIDAS DIFERENTES";
    else cout << "\nSAIDAS IGUAIS";
}

void Funcoes::CalculatePi(const char *padrao, int *pi){
    pi[0] = 0;
    int k, l;

    for(int i = 1; padrao[i] != '\0'; ++i){
        k = i - 1;
        while(true){
            l = pi[k];
            if (l == 0){
                if(padrao[0] == padrao[i]){
                    pi[i] = 1;
                    break;
                } else {
                    pi[i] = 0;
                    break;
                }
            } else {
                if(padrao[i] == padrao[l]){
                    pi[i] = l + 1;
                    break;
                } else {
                    k = l - 1;
                }
            }
        }
    }
}

void Funcoes::KnuthMorrisPratt(const char *texto, const char *padrao, int *saida){
    int m = strlen(padrao), n = strlen(texto);
    int *pi = new int[m];
    CalculatePi(padrao, pi);
    int i = 0, j = 0;

    while(texto[i] != '\0'){
        if(texto[i] != padrao[j]){
            if(j == 0) ++i;
            else j = pi[j-1];
        } else {
            if (j == m - 1){
                *saida = i -j;
                ++saida;
                j = pi[j];
                ++i;
            } else {
                ++i;
                ++j;
            }
        }
    }
    *saida = -1;
}

void Funcoes::ForcaBruta(const char *texto, const char *padrao, int *saida){
    int posicao_ocorrencia = 0; // guarda a posicao do texto em que comecou a ocorrencia do padrao
    int posicao_corrente = 0; // posicao corrente do texto
    int posicao_padrao = 0;
    while(texto[posicao_corrente] != '\0'){
        if(texto[posicao_corrente] == padrao[0] && posicao_padrao == 0){ // inicio do padrão
            posicao_ocorrencia = posicao_corrente;
            ++posicao_padrao;
        }   else if (texto[posicao_corrente] == padrao[posicao_padrao]){ // vai batendo com os caracteres do padrao
            ++posicao_padrao;
        }   else if(texto[posicao_corrente] != padrao[posicao_padrao] && posicao_padrao != 0){ // caso não seja bata mas estava batendo antes
            posicao_corrente = posicao_ocorrencia;
            posicao_padrao = 0;
        }
        ++posicao_corrente;
        if(padrao[posicao_padrao] == '\0' && posicao_padrao != 0){ // ve se chegou no fim do padrao
            posicao_corrente = posicao_ocorrencia + 1; // la embaixo ele incrementa o + 1
            posicao_padrao = 0;
            *saida = posicao_ocorrencia;
            ++saida;
        } 
    }
    
    *saida = -1;
}

void Funcoes::InstanciaAleatoria(int n, int m, char l, char* texto, char* padrao){
    srand(time(NULL));

    for(int i = 0; i < n; i++)
        texto[i] = 'a' + (rand()%l);   
    texto[n] = '\0';

    for(int i = 0; i < m; ++i)
        padrao[i] = 'a' + (rand()%l);
    padrao[m] = '\0';
}

void Funcoes::PiorCaso1(int n, int m, char* texto, char* padrao){
    for(int i = 0; i < n; i++)
        texto[i] = 'a';   
    texto[n] = '\0';

    for(int i = 0; i < m - 1; ++i)
        padrao[i] = 'a';
    padrao[m-1] = 'b';
    padrao[m] = '\0';
}

void Funcoes::PiorCaso2(int n, int m, char* texto, char* padrao){
    for(int i = 0; i < n; i++)
        texto[i] = 'a';   
    texto[n] = '\0';

    for(int i = 0; i < m; ++i)
        padrao[i] = 'a';
    padrao[m] = '\0';
}

void Funcoes::completeZeros(int* vetor, int tamanho){
    for(int *i = vetor; i != vetor+tamanho;++i)
        *i = 0;
}