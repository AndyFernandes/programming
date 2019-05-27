#include <iostream>
#include <map>
#include "Heap.cpp"
#include <set>
#include <algorithm>
#include <functional>
using namespace std;
typedef map<char, int> dict;
typedef pair<char, int> par;
// typedef function<bool(dict, dict)> comparator;

void print_vector(int *inicio, int *fim){
    cout << "\n";
    for(; inicio != fim; inicio++){
        cout << *inicio << "  ";
    }
    cout << "\n";
}

dict countChar(char* pText){
    dict m;
    while(*pText != '\0'){
        if (m[*pText])
            m[*pText] += 1;
        else
            m[*pText] = 1;
        pText++;
    }
    return m;
}

int main(){
    // int vetor[] =  {28,58,49,69,52,69,40,75,71,82};
    // int vetor[] =  {4,1,3,2,16,9,10,14,8,7};
    Heap heap;
    // heap.construir(vetor, 10);
    // // print_vector(vetor, vetor+15);
    // print_vector(heap.heap, heap.heap + heap.heapSize);
    // cout << "Minimo " << heap.minimum() << endl;
    // int min = heap.extractMinimum();
    // cout << "Minimo " << min << endl;
    // print_vector(heap.heap, heap.heap + heap.heapSize);

    // heap.insert(3);
    // heap.insert(50);
    // heap.insert(7);
    // heap.insert(6);    
    // dict countSymbols;
    // m['A'] = 2;

    dict countSymbols = countChar("A arina e louca");
    
    for(par element: countSymbols){
    //    cout << element.first << " : " << element.second << endl;
        heap.insert(element.second);
    }

    // TODO FAZER UMA STRUCT
    return 0;
}