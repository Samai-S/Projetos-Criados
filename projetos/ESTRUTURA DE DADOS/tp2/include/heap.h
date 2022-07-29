#include <iostream>
#include <string>
#include <fstream>
#include "struct.h"

using namespace std;

#ifndef HEAP_H
#define HEAP_H

//inicializacao da classe heap

class Heap
{
public:
  Heap();
  //~Heap();
  void AddItem(int, int,int, string);
  void HeapSize(int);
  void constroi(int, int);
  void heapSort();
  void printHeap();
  tupla RemoveMaior(string);

private:
  int n;
  estrutura *A;
  int Tamanho;
};

#endif
