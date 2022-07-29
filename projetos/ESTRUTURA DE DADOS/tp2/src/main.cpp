#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include "heap.h"
#include "quicksort.h"
#include "struct.h"
#include"processaheap.h"

using namespace std;

void printArquivo(estrutura *arr, int n, string nomearquivo)
//Funcao recebe um array estrutura, um numero n referente ao número de execucoes e uma string com nome do arquivo
//Nessa funcao os arquivo com nome da string eh aberta e eh escrito as arrays estrutura com as paginas e acessos de cada pagina
{
  int i;
  ofstream ofs(nomearquivo);

  for (i = 0; i < n; i++)
    ofs << arr[i].URL << " " << arr[i].prioridade << endl;

  ofs.close();
}

int main()
{ 
  //declaracao das variaveis que serao utilizadas na mein

  int fitas = 0, linhas = 0, tamanhoMEMORIA = 0, rodada = 1, count = 0, j = 0, numero = 0, resto = 0, countfitas = 0;
  string file_name, line, nomearquivo, nomeoriginal, novonome, extencao, StrRodada, url;
  stringstream str;

 //inicializacao do nome do arquivo de entrada, tamanho da memória e nome do arquivo de saida
  cout << "Nome Arquivo: ";
  cin >> file_name;

  nomeoriginal = "rodadas";
  extencao = ".txt";
  StrRodada = to_string(rodada);
  novonome = nomeoriginal + StrRodada + extencao;
  //conta quantas linhas tem no arquivo de entrada
  ifstream ifs1(file_name);
  while (getline(ifs1, line))
  {
    linhas++;
  }

  ifs1.close();

  cout << "Tamanho Memória: ";
  cin >> tamanhoMEMORIA;

  if(tamanhoMEMORIA>linhas){
    tamanhoMEMORIA=linhas;
  }

  cout << "Nome arquivo saída: ";
  cin >> nomearquivo;

  resto = linhas % tamanhoMEMORIA;
  fitas = (linhas - resto) / tamanhoMEMORIA;

  ifstream ifs(file_name);

  estrutura arr[tamanhoMEMORIA];
  //executa o quicksort através da leitura de cada linha do arquivo
  while (getline(ifs, line))
  {
    str.clear();
    str << line;
    str >> url >> numero;

    arr[j].prioridade = numero;
    arr[j].URL = url;

    j++;

    count++;

    if (count == tamanhoMEMORIA)
    {
      quickSort(arr, 0, j - 1);
      printArquivo(arr, j, novonome);

      rodada++;
      StrRodada = to_string(rodada);
      novonome = nomeoriginal + StrRodada + extencao;
      count = 0;
      j = 0;
      countfitas++;
      if (countfitas == fitas)
      {
        j = 0;
        break;
      }
    }
  }

  if (resto > 0)
  {
    countfitas++;
    estrutura arr2[resto];
    while (getline(ifs, line))
    {
      str.clear();
      str << line;
      str >> url >> numero;

      arr2[j].prioridade = numero;
      arr2[j].URL = url;

      j++;
    }

    quickSort(arr2, 0, j - 1);
    printArquivo(arr2, j, novonome);

    ifs.close();
    
  }
  //limpa o arquivo caso haja um existente com o mesmo nome
  ofstream ofs(nomearquivo);
  ofs.clear();
  ofs.close();
  
  processaHeap(countfitas, tamanhoMEMORIA, linhas-1, nomearquivo);
  
}
