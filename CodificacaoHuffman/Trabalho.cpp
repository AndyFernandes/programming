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
    int vetor[] =  {28,58,49,69,52,69,40,75,71,82};
    Heap heap;
    heap.construir(vetor, 10);
    // print_vector(vetor, vetor+15);
    print_vector(heap.heap, heap.heap+10);

    return 0;
}    