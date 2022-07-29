#include "heap.h"

Heap::Heap()
//inicializacao da variavel da classe
{
  n = 0;
}

void Heap::HeapSize(int tamanho)
//Passado como parametro um inteiro tamanho que sera utilizado para inicializacao do array estrutura 
{
  Tamanho = tamanho;
  A = new estrutura[tamanho];
}

void Heap::AddItem(int valor, int fita, int indice, string nome)
//Parametros: valor da estrutura, a fita na qual ele veio, o indice dele na fita e o nome da string
//Adiciona uma variavel do tipo struct na fila
{
  if (n < Tamanho)
  {
    A[n].prioridade = valor;
    A[n].fita = fita;
    A[n].URL = nome;
    A[n].indice = indice;

    n++;
  }
  //caso o array esteja cheio ele substitui a primeira posicao por um novo
  else
  {
    A[0].prioridade = valor;
    A[0].fita = fita;
    A[0].URL = nome;
    A[0].indice = indice;
  }
}

void Heap::constroi(int tamanho, int i)
{
//Recebe o tamanho e o a um valor i conforme a posicao do i no for da funçao heapsort
//Organiza o array em forma de heap
  int maior = i;
  int esq = 2 * i + 1;
  int dir = 2 * i + 2;
  estrutura AUX;

  //realiza as condicoes de comparacao entre o valor das variáveis caso sejam iguais o métododo de desenpate eh a ordenacao alfabetica
  if ((esq < tamanho && A[esq].prioridade > A[maior].prioridade) || (esq < tamanho && A[esq].prioridade == A[maior].prioridade && A[esq].URL.compare(A[maior].URL) <0))
    maior = esq;

  if ((dir < tamanho && A[dir].prioridade > A[maior].prioridade) || (dir < tamanho && A[dir].prioridade == A[maior].prioridade && A[dir].URL.compare(A[maior].URL) <0))
    maior = dir;

//chama recursivamente para ordenar o heap
  if (maior != i)
  {
    AUX = A[i];
    A[i] = A[maior];
    A[maior] = AUX;
    constroi(tamanho, maior);
  }
}

void Heap::heapSort()
//chama a funcao constroi para criacao do heap
{
  for (int i = n / 2 - 1; i >= 0; i--)
    constroi(n, i);
}

void Heap::printHeap()
//funcao imprime o heap
{
  for (int i = 0; i < n; i++)
    cout << A[i].URL << " " << A[i].prioridade << endl;
}

tupla Heap::RemoveMaior(string str)
//funcao para escrever a primeira variavel da posicao do heap no arquivo de texto
//retorna uma tupla da fita da variavel que ela estava e seu indice no arquivo de texto, isso facilita a utilizacao de interacoes de loops 
{
  tupla t;
  ofstream file(str, ios::app);
  if (A[0].prioridade > -1)
  {
    file << A[0].URL << " " << A[0].prioridade << endl;
  }

  t.value1 = A[0].fita;
  t.value2 = A[0].indice;
  return t;
}
