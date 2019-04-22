#include <iostream>
using namespace std;

//DOING
void subseq_intuitivo(char *texto, char *padrao, int *saida){
    int posicao_ocorrencia = 0; // guarda a posicao do texto em que comecou a ocorrencia do padrao
    int posicao_corrente = 0; // posicao corrente do texto
    char *i = texto;
    char *p = padrao;
    while(*i != '\0'){
        if(*i == *p){
            if(p == padrao){ // verifica se está comparando o primeiro caracter do padrão, aí eu atualiza a posicao_ocorrencia
                posicao_ocorrencia = posicao_corrente;
            } else if(*(padrao+1) == '\0')  { // verifica se o próximo caracter é o final do padrão
                // guarda a posicao_ocorrencia no vetor de saida e incrementa o vetor
                *saida = posicao_ocorrencia;
                ++saida;
                p = padrao;
                // volta o i pra posicao_ocorrencia + 1
                i = texto + posicao_ocorrencia + 1;
            }
            ++p;
        } 
        ++i;
        ++posicao_corrente;
    }
}

int main(){
    char texto[] = "a vida é bela e quando bem vivida é viciosa";
    char padrao[]= "vi";
    return 0;
}