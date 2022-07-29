#ifndef CHAVE
#define CHAVE
#include<iostream>
#include<string>

//struct para utilizacao da estrutura que contem o valor prioridade equivalente ao numero de visitas, fita da fita que a variavel veio
//URL que equivale a pagina e o indice que equivale a posicao no arquivo
typedef struct chave
{
  int prioridade;
  int fita;
  std::string URL;
  int indice;

}estrutura;

//struct tupla para funcoes que retornam dois valores;
typedef struct tupla
{
  int value1;
  int value2;

}tupla;

#endif

