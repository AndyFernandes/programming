// By Andreza Fernandes de Oliveira, may/2019

#include <iostream>
using namespace std;

void calculatePi(char *padrao, int *pi, int m){
    *pi = 0;
    ++pi;
    int k;
    for(int i = 1; i < m-1; ++i){
        k = i - 1;
        while(true){
            int l = pi[k];
            if (l == 0){
                if(padrao[0] == padrao[i]){
                    pi[i] = 1;
                    break;
                } else {
                    pi[i] = 0;
                    break;
                }
            } else {
                if(padrao[i] == padrao[l]){
                    pi[i] = l + 1;
                    break;
                } else {
                    k = l - 1;
                }
            }
        }
    }
}

void kmp(){

}

int main(){
    return 0;
}