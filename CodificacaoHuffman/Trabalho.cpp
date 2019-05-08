#include <iostream>
#include "Heap.cpp"
using namespace std;

void print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

int main(){
    int vetor[] =  {1, 20, 51, 3, 5, 100, -1, 30, 2, 4, 25, 24, 30, 19, 14};
    Heap heap;
    heap.construir(vetor, 15);
    // print_vector(vetor, vetor+15);
    print_vector(heap.heap, heap.heap+15);

    return 0;
}