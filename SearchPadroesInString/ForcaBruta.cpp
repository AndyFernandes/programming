#include <iostream>
#include <string.h>
using namespace std;

//DOING
void buscar(char *texto, char *padrao, int *saida){
    int posicao_ocorrencia = 0; // guarda a posicao do texto em que comecou a ocorrencia do padrao
    int posicao_corrente = 0; // posicao corrente do texto
    int posicao_padrao = 0;
    while(texto[posicao_corrente] != '\0'){
        if(padrao[posicao_padrao] == '\0' && posicao_padrao != 0){ // ve se chegou no fim do padrao
            posicao_corrente = posicao_ocorrencia; // la embaixo ele incrementa o + 1
            posicao_padrao = 0;
            *saida = posicao_ocorrencia;
            ++saida;
        }   else if(*texto == padrao[0] && posicao_padrao == 0){ // inicio do padrão
            posicao_ocorrencia = posicao_corrente;
            ++posicao_padrao;
        }   else if (*texto == padrao[posicao_padrao]){ // vai batendo com os caracteres do padrao
            ++posicao_padrao;
        }   else if(*texto != padrao[posicao_padrao] && posicao_padrao != 0){ // caso não seja bata mas estava batendo antes
            posicao_corrente = posicao_ocorrencia + 1;
            posicao_padrao = 0;
        }
        ++posicao_corrente;
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
    char texto[] = "vi";
    char padrao[]= "vi";
    int* saida = new int[strlen(texto) + 1];
    buscar(texto, padrao, saida);
    print_vector(saida, saida + strlen(texto) + 1);
    return 0;
}