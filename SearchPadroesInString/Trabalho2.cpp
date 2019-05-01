// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include <random>
#include <new>
#include <time.h>
#include "Funcoes.cpp"
#include "instancias_Reais_Trabalho_2.hpp"
using namespace std;

Funcoes func;
void run(const char *texto, const char *padrao){
    //int* fim = vetor + tamanho;
    clock_t inicio;
    clock_t total;

    inicio = clock();
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nFORÇA BRUTA: " << ((float)total/CLOCKS_PER_SEC) << " seconds.";
    cout << "\n========================================================================\n";

    inicio = clock();
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nKNUTH MORRIS PRATT: " << ((float)total/CLOCKS_PER_SEC) << " seconds.";
    cout << "\n========================================================================\n";

    delete[] texto;
    delete[] padrao;
}

void menu(){
    int tamanho;
    int opcao;
    int continuar;
    int n, m;
    const char* texto; //= new char[tamanho];
    const char* padrao;

    cout << "\n1. INSTANCIA ALEATORIA \n2. INSTANCIA PIOR CASO 1 \n3. INSTANCIA PIOR CASO 2 \n4. INSTANCIA TEXTO REAIS \nINFORME A OPCAO DESEJADA: ";
    cin >> opcao;

    if(opcao == 4){
        texto = Texto_Livros;
        cout << "\nESCOLHA UM NUMERO DE 0 A 35129: ";
        cin >> n;
        if(n >= 0 && n < 35129)
            padrao = Padroes_Palavras[n];

    } else {
        cout << "\nDIGITE O TAMANHO DO TEXTO: ";
        cin >> n;

        cout << "\nDIGITE O TAMANHO DO PADRÃO: ";
        cin >> m;
        
        //fzr um do while aqui
        //if(m <= n){}
        switch (opcao){
            case 1:
                func.InstanciaAleatoria(n, m, texto, padrao);
                break;
            case 2:
                func.PiorCaso1(n, m, texto, padrao);
                break;
            case 3:
                func.PiorCaso2(n, m, texto, padrao);
                break;
            default:
                cout << "\nOPCAO INVALIDA!\nPor favor, tente novamente\n";
                break;
        }
    }

    run(texto, padrao);
}

int main(){
    int continuar = 1;
    do {
        menu();
        cout << "\n--------------------------------------------------------------------\n";
        cout << "VOCE DESEJA CONTINUAR? \n1. SIM \n2. NAO \n:";
        cin >> continuar;
    } while(continuar == 1);
    
    return 0;
}