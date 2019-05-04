// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include <string.h>
#include "instancias_Reais_Trabalho_2.hpp"
using namespace std;

// TODO: Deixar tudo em ponteiro
void ForcaBruta(const char *texto, const char *padrao, int *saida){
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

void print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

void completeZeros(int* vetor, int tamanho){
    for(int *i = vetor; i != vetor+tamanho;++i)
        *i =0;
}
int main(){
    const char* texto = Texto_Livros;
    char padrao[]= "a";
    cout << strlen(texto);

    int tamanho = strlen(texto) + 1;
    int* saida = new int[tamanho];
    completeZeros(saida, tamanho);
    ForcaBruta(texto, padrao, saida);
    print_vector(saida, saida + strlen(texto) + 1);
 
    delete[] saida;
    return 0;
}