// By Andreza Fernandes de Oliveira, april/2019

#include <iostream>
#include <tuple>
using namespace std;

class QuickSortVersions{
    public:
        int* BFPRT(int* inicio, int* fim, int *pivo);
        void QuickSortIndice(int *inicio, int *fim);
        void QuickSortAleatorio(int *inicio, int *fim);
        void QuickSortMemoria(int *inicio, int *fim);
        void QuickSortLomuto(int *inicio, int *fim);
        void QuickSortTriplo(int *inicio, int *fim);
        void QuickSortHoare(int *inicio, int *fim);
        void QuickSortBFPRT(int *inicio, int *fim);
}