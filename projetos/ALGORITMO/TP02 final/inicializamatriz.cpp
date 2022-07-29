#include<iostream>

using namespace std;

void inicializamatriz(int **matriz, int n_cidades)
{
    int i = 0, j = 0;
    for (i = 0; i < n_cidades; i++)
    {
        for (j = 0; j < n_cidades; j++)
        {
            matriz[i][j] = -1;
        }
    }
}

void preeencheMatriz(int *matriz[], int caminhos)
{
    int i = 0, valor1=0, valor2=0, distancia=0;
    while (i < caminhos)
    {
        cin >> valor1 >> valor2 >> distancia;
        matriz[valor1 - 1][valor2 - 1] = distancia;
        i++;
    }
}