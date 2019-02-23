#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

bool sao_iguais(const char *r, const char *s){
    while(*r != '\0' || *s != '\0'){
        if(*r != *s)
            return false;
        r++;
        s++;
    }
    return true;
}

void inverter(int *v, int n){
    int aux[n];
    int *q = aux;
    int *fim = v + n;

    // copiar p/ auxiliar
    for(int *p = v; p != fim; ++p){
        *q = *p;
        q++;
    }
    q = aux + n - 1 ;
    // inverter
    for(int *p = v; p != fim; ++p){
        *p = *q;
        --q;
        cout << *p << " ";
    }
}


int main(void){  
    char str1[] = "o";
    char str2[] = "o";
    //char fim[] = {'\0'};
    //for(char *i = str1; i !=  fim; ++i){
    //    cout << *i << "\n";
    //}
    ////////////////////// 1a questao
    bool a = sao_iguais(str1, str2); 
    if(a)
        cout << "true" << endl;
    else
        cout << "false" << endl;
    
    ////////////////////// 2a questao
    int n = 7;
    int v[n] = {7, 6, 5, 4, 3, 2, 1};
    inverter(v, n);
}