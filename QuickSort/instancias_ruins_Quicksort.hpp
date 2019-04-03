// Author: Pablo M. S. Farias (pablo@dc.ufc.br). Date: 2019-04-03.

/* -----------------------------------------------------------------------------
 * EXPLICAÃ‡ÃƒO DESTE ARQUIVO:
 *
 * Este arquivo possui uma funÃ§Ã£o "escrever_instancia", que constrÃ³i uma
 * instÃ¢ncia de pior caso para um Quicksort baseado numa escolha "fixa" de pivÃ´.
 *
 * Mais precisamente, as instÃ¢ncias geradas causarÃ£o o pior caso do Quicksort
 * quando:
 *
 *   1. Para ordenar o intervalo de vetor que vai do Ã­ndice "primeiro" ao Ã­ndice
 *      "ultimo", o Quicksort sempre escolhe como pivÃ´ o elemento cujo Ã­ndice Ã©
 *      o valor retornado pela funÃ§Ã£o
 *
 *        int escolher_pivo (int primeiro, int ultimo)
 *
 *      a qual deve fazer um cÃ¡lculo baseado exclusivamente nos dois argumentos
 *      recebidos.
 *
 *   2. O Quicksort realiza o particionamento por meio do algoritmo de Lomuto,
 *      especificamente a versÃ£o na qual o pivÃ´ Ã© inicialmente trocado com o
 *      elemento do inÃ­cio do intervalo, e depois reposicionado ao final do
 *      particionamento.
 *
 *      ObservaÃ§Ã£o: nÃ£o importa se o particionamento deixa ou nÃ£o os elementos
 *      iguais ao pivÃ´ todos juntos no "meio" do intervalo, pois as instÃ¢ncias
 *      geradas nÃ£o possuem elementos repetidos.
 *
 * A funÃ§Ã£o "escrever_instancia" possui a seguinte especificaÃ§Ã£o:
 *
 *   1. O primeiro argumento Ã© o vetor "v" no qual deve ser escrita a instÃ¢ncia.
 *
 *   2. O segundo argumento Ã© o nÃºmero "n" de elementos da instÃ¢ncia a ser
 *      escrita.
 *
 *   3. O valor de retorno Ã© do tipo "bool":
 *
 *      * true:  indica erro (falta de memÃ³ria);
 *      * false: indica sucesso.
 *
 * -------------------------------------------------------------------------- */

#ifndef INSTANCIAS_RUINS_QUICKSORT_HPP
#define INSTANCIAS_RUINS_QUICKSORT_HPP

// -----------------------------------------------------------------------------

#include <new>

using std::nothrow;

#include <utility>

using std::swap;

// -----------------------------------------------------------------------------

int escolher_pivo (int primeiro, int ultimo);


// VALOR DE RETORNO: * true:  indica erro (falta de memÃ³ria);
//                   * false: indica sucesso.
//
template <typename T>
bool escrever_instancia (T *v, int n)
  {
   int i;  int *pos = new(nothrow) int[n];  if (pos == nullptr) return true;

   for (i = 0; i < n; ++i) pos[i] = i;

   for (i = n-1; i != -1; --i)
     {
      int p = escolher_pivo(0,i);  v[ pos[p] ] = i;

      swap( pos[p], pos[0] );  swap( pos[0], pos[i] );
     }

   delete[] pos;  return false;
  }

// -----------------------------------------------------------------------------

#endif