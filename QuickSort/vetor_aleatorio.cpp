#include <random>
#include <iostream>
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "-----------------------------------------------------------------------------------------------\n\t\t";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n---------------------------------------------------------------------------------------------\n";
}

int main(){
    int tamanho = 15;
    // int vetor[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    // int *pivo = vetor + 4; 
    random_device rd;
    mt19937 ger(rd());
    uniform_int_distribution<int> dis(1, 6);
    
    int meu_num = dis(ger);
    cout << meu_num;
  return 0;
}