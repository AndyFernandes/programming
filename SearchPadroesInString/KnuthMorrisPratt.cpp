// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include <string.h>
using namespace std;

void calculatePi(const char *padrao, int *pi, int m){
    *pi = 0;
    ++pi;
    int k, l;
    for(int i = 1; i < m-1; ++i){
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
    calculatePi(padrao, pi, m);
    int i = 0, j = 0;

    while(i < n){
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
}

void print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

int main(){
    char texto[] = "vi um passaro vivido";
    char padrao[]= "vi";
    int* saida = new int[strlen(texto) + 1];
    cout << texto;
    KnuthMorrisPratt(texto, padrao, saida);
    cout << texto;
    print_vector(saida, saida + strlen(texto) + 1);
    return 0;
}