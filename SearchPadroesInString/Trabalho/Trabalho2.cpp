// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
#include <random>
#include <new>
#include <time.h>
#include <string.h>
#include "Funcoes.cpp"
#include "instancias_Reais_Trabalho_2.hpp"
using namespace std;

Funcoes func;
void run(const char *texto, const char *padrao){
    int* saidaFB = new int[strlen(texto) + 1];
    int* saidaKMP = new int[strlen(texto) + 1];
    func.completeZeros(saidaFB, strlen(texto) + 1);
    func.completeZeros(saidaKMP, strlen(texto) + 1);

    clock_t inicio;
    clock_t total;

    inicio = clock();
    func.ForcaBruta(texto, padrao, saidaFB);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nFORÇA BRUTA: " << ((float)total/CLOCKS_PER_SEC) << " seconds.";
    cout << "\n========================================================================\n";

    inicio = clock();
    func.KnuthMorrisPratt(texto, padrao, saidaKMP);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nKNUTH MORRIS PRATT: " << ((float)total/CLOCKS_PER_SEC) << " seconds.";
    cout << "\n========================================================================\n";

    delete[] saidaFB;
    delete[] saidaKMP;
}

void menu(){
    int tamanho;
    int opcao;
    int continuar;
    int n, m;

    cout << "\n1. INSTANCIA ALEATORIA \n2. INSTANCIA PIOR CASO 1 \n3. INSTANCIA PIOR CASO 2 \n4. INSTANCIA TEXTO REAIS \nINFORME A OPCAO DESEJADA: ";
    cin >> opcao;

    if(opcao == 4){
        do{
            cout << "\nESCOLHA UM NUMERO VALIDO DE 0 A 35129: ";
            cin >> n;
        } while(n < 0 || n >= 35129);

        const char* texto = Texto_Livros;
        const char* padrao = Padroes_Palavras[n];
    
        cout << *texto << endl;
        cout << *padrao;
        run(texto, padrao);
    } else if(opcao <= 4 && opcao >= 0){ 
        do{
            cout << "\nATENÇÃO: TAMANHO DO PADRAO DEVE SER <= TAMANHO DO TEXTO.";
            cout << "\nDIGITE O TAMANHO DO TEXTO: ";
            cin >> n;

            cout << "\nDIGITE O TAMANHO DO PADRÃO: ";
            cin >> m;
        } while(m > n);

        char* texto = new char[n];
        char* padrao = new char[m];
        
        switch (opcao){
            case 1:
                int l;
                cout << "\nDIGITE O L: ";
                cin >> l;
                func.InstanciaAleatoria(n, m, l, texto, padrao);
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

        run(texto, padrao);
    } else {
        cout << "\nOPCAO INVALIDA!\nPor favor, tente novamente\n";
        return;
    }
    // printf(texto);
    // printf(padrao);
}

int main(){
    int continuar = 1;
    do {
        system("clear");
        //system("cls");
        menu();
        cout << "\n--------------------------------------------------------------------\n";
        cout << "VOCE DESEJA CONTINUAR? \n1. SIM \n2. NAO \n:";
        cin >> continuar;
    } while(continuar == 1);
    
    return 0;
}