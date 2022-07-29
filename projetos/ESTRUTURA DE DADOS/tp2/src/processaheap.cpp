
#include "processaheap.h"

void processaHeap(int countfitas, int tamanhoMEMORIA, int tamanhototal, string nomearquivo)
//Funcao recebe um valor da quantidade de fitas, tamanho da memoria, tamanho total do arquivo e o nome do arquivo de saida
//Funcao cria um arquivo com todas as arrays organizadas
{
  //declaracao de variaveis para a execucao da funcao
  int i = 0, j = 0, numero = 0;
  tupla fitaMaior;
  string novonome, nomeoriginal, extencao, StrRodada, linha, url;
  estrutura matrix[countfitas][tamanhoMEMORIA];
  nomeoriginal = "rodadas";
  extencao = ".txt";

  //inicializar uma matriz de tamanho countfitas x tamanho memoria com valores de visitas = -1
  for (i = 0; i < countfitas; i++)
  {
    for (j = 0; j < tamanhoMEMORIA; j++)
    {
      matrix[i][j].prioridade = -1;
    }
  }


  for (j = 0; j < countfitas; j++)
  //loop para preencher a matriz com todos os elementos das fitas
  {
    StrRodada = to_string(j + 1);
    novonome = nomeoriginal + StrRodada + extencao;
    stringstream str;
    ifstream ifs2(novonome);
    i = 0;

    while (getline(ifs2, linha))
    {

      str.clear();
      str << linha;
      str >> url >> numero;

      matrix[j][i].prioridade = numero;
      matrix[j][i].URL = url;
      matrix[j][i].fita = j + 1;
      matrix[j][i].indice = i;

      i++;
    }
    ifs2.close();
  }

  //inicializacao do heap e a um loop com o primeiro elemento de cada arquivo no heap
  Heap heap;
  heap = Heap();
  heap.HeapSize(countfitas);
  for (i = 0; i < countfitas; i++)
    heap.AddItem(matrix[i][0].prioridade, matrix[i][0].fita, matrix[i][0].indice, matrix[i][0].URL);

  j = 0;
  
  //organiza o heapsort recebe os valores da tupla para continuar a execucao a partir da posicao retornada no removeMaior
  heap.heapSort();
  fitaMaior = heap.RemoveMaior(nomearquivo);
  matrix[fitaMaior.value1 - 1][fitaMaior.value2].prioridade = -1;

  //for para reorganizar a fita a partir do heap e dos parametros do struct que possibilitou excluir a utilizacao de outro loop
  for (i = 0; i < tamanhototal; i++)
  {
    heap.AddItem(matrix[fitaMaior.value1 - 1][fitaMaior.value2 + 1].prioridade, matrix[fitaMaior.value1 - 1][fitaMaior.value2 + 1].fita, matrix[fitaMaior.value1 - 1][fitaMaior.value2 + 1].indice, matrix[fitaMaior.value1 - 1][fitaMaior.value2 + 1].URL);
    heap.heapSort();
    fitaMaior = heap.RemoveMaior(nomearquivo);
    matrix[fitaMaior.value1 - 1][fitaMaior.value2].prioridade = -1;
  }
}
