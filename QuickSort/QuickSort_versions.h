#if !defined(QuickSort_versions)
#define QuickSort_versions
#include <tuple>
using namespace std;

void print_vector(int *inicio, int *fim);
void trocar(int* posicao1, int *posicao2);
int* Particao_Lomuto(int *inicio, int *pivo, int *fim);
tuple<int*, int*> Particao_Tripla(int *inicio, int *pivo, int *fim);
void Selecao_Hoare(int *inicio, int *fim, int *i);
int* BFPRT(int* inicio, int* fim, int *pivo);
void QuickSort_Lomuto(int *inicio, int *pivo, int *fim);
void QuickSort_Triplo(int *inicio, int *pivo, int *fim);
void QuickSort_Hoare(int *inicio, int *pivo, int *fim);
void QuickSort_Cauda(int *inicio, int *pivo, int *fim);
void QuickSort_BFPRT(int *inicio, int *pivo, int *fim);
#endif