// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include <random>
#include <new>
#include <time.h>
#include "QuickSortVersions.cpp"
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

QuickSortVersions quick;
void runQuickSortVersions(int *vetor, int tamanho){
    int* fim = vetor + tamanho;
    clock_t inicio;
    clock_t total;

    inicio = clock();
    int* copia = func.copy_vector(vetor, tamanho);
    quick.QuickSortIndice(copia, 0, tamanho -1);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nQUICKSORT VIA INDICE: " << ((float)total/CLOCKS_PER_SEC);
    func.check(copia, copia + tamanho);
    func.print_vector(copia, copia + tamanho);
    cout << "\n========================================================================\n";

    inicio = clock();
    copia = func.copy_vector(vetor, tamanho);
    quick.QuickSortLomuto(copia, copia + tamanho -1);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nQUICKSORT VIA PARTICIONAMENTO DUPLO: " << ((float)total/CLOCKS_PER_SEC);
    func.check(copia, copia + tamanho);
    func.print_vector(copia, copia + tamanho);
    cout << "\n========================================================================\n";

    inicio = clock();
    copia = func.copy_vector(vetor, tamanho);
    quick.QuickSortTriplo(copia, copia + tamanho -1);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nQUICKSORT VIA PARTICIONAMENTO TRIPLO: " << ((float)total/CLOCKS_PER_SEC);
    func.check(copia, copia + tamanho);
    func.print_vector(copia, copia + tamanho);
    cout << "\n========================================================================\n";

    inicio = clock();
    copia = func.copy_vector(vetor, tamanho);
    quick.QuickSortMemoria(copia, copia + tamanho -1);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nQUICKSORT MEMORIA LOG(N): " << ((float)total/CLOCKS_PER_SEC);
    func.check(copia, copia + tamanho);
    func.print_vector(copia, copia + tamanho);
    cout << "\n========================================================================\n";

    inicio = clock();
    copia = func.copy_vector(vetor, tamanho);
    quick.QuickSortBFPRT(copia, copia + tamanho -1);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nQUICKSORT VIA MEDIANA DAS MEDIANAS: " << ((float)total/CLOCKS_PER_SEC);
    func.check(copia, copia + tamanho);
    func.print_vector(copia, copia + tamanho);
    cout << "\n========================================================================\n";

    inicio = clock();
    copia = func.copy_vector(vetor, tamanho);
    quick.QuickSortAleatorio(copia, copia + tamanho -1);
    total = clock() - inicio;
    cout << "\n========================================================================";
    cout << "\nQUICKSORT PIVO ALEATORIO: " << ((float)total/CLOCKS_PER_SEC);
    func.check(copia, copia + tamanho);
    func.print_vector(copia, copia + tamanho);
    cout << "\n========================================================================\n";
}

void menu(){
    int tamanho;
    int opcao;
    int continuar;
    int* vetor;

    cout << "DIGITE O TAMANHO DO VETOR: ";
    cin >> tamanho;

    cout << "\n1. GERADOR DE INSTANCIAS RUINS \n2. GERADOR DE VETOR ALEATORIO \nINFORME A OPCAO DESEJADA: ";
    cin >> opcao;

    switch (opcao){
        case 1:
            if(escrever_instancia(vetor, tamanho)){
                cout << "a";
            } else {
                func.print_vector(vetor, vetor + tamanho);
            }
            
            break;
        case 2:
            int valor_inicial, valor_final;
            cout << "\nVALOR INICIAL DO INTERVALO: ";
            cin >> valor_inicial;

            cout << "VALOR FINAL DO INTERVALO: ";
            cin >> valor_final;
            vetor = func.vetor_aleatorio(tamanho, valor_inicial, valor_final);
            func.print_vector(vetor, vetor + tamanho);
            break;
        default:
            cout << "\nOPCAO INVALIDA!\nPor favor, tente novamente\n";
            break;
    }

    runQuickSortVersions(vetor, tamanho);
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