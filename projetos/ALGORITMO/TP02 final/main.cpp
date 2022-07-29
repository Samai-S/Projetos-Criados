#include <iostream>
#include "pesquisa.cpp"
#include "inicializamatriz.cpp"

using namespace std;



int main()
{
    int i = 0; 
    int n_cidades, caminhos, consultas;

    cin >> n_cidades >> caminhos >> consultas;
  
    int **matriz;

    matriz = new int *[n_cidades];

    for (i = 0; i < n_cidades; i++)
    {
        matriz[i] = new int[n_cidades];
    }

    inicializamatriz(matriz, n_cidades);

    preeencheMatriz(matriz, caminhos);

    pesquisas(matriz,n_cidades,caminhos,consultas);

  
}