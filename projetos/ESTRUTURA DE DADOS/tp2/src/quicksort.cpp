#include "quicksort.h"

using namespace std;

int particao(estrutura *A, int inicio, int fim)
//A funcao recebe um array de estrutura e dois inteiros um sendo o primeiro posicao do array para a ultima
//funcao organiza o array
{
  estrutura pivo = A[fim];
  estrutura aux;

  int i = (inicio - 1);

//loop para verificar cada elemento do array comparando-o com o pivo
  for (int j = inicio; j < fim; j++)
  {
    int compare = A[j].URL.compare(pivo.URL);
    if ((A[j].prioridade > pivo.prioridade) || (A[j].prioridade == pivo.prioridade && compare < 0))
    {
      i++;
      aux = A[i];
      A[i] = A[j];
      A[j] = aux;
    }
  }
  aux = A[i + 1];
  A[i + 1] = A[fim];
  A[fim] = aux;

  return (i + 1);
}

void quickSort(estrutura *A, int inicio, int fim)
//Funcao que recebe um array de estrutura o inicio e o fim do array
//funcao recursiva para reorganizar a partir da funcao particao que seleciona o pivo e recursivamente realiza o quicksort para esquerda e depois direita do pivo
{
  if (inicio < fim)
  {
    int pi = particao(A, inicio, fim);
    quickSort(A, inicio, pi - 1);
    quickSort(A, pi + 1, fim);
  }
}
