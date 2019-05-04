// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include <string.h>
using namespace std;

void calculatePi(const char *padrao, int *pi){
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

void KnuthMorrisPratt(const char* texto, const char* padrao, int* saida){
    int m = strlen(padrao), n = strlen(texto);
    int *pi = new int[m];
    calculatePi(padrao, pi);
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

void print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

int main(){
    const char texto[] = "AAAAAAAAAAAAAAAA";
    const char padrao[]= "C";
    int* saida = new int[strlen(texto) + 1];
    KnuthMorrisPratt(texto, padrao, saida);
    print_vector(saida, saida + strlen(texto) + 1);
    return 0;
}