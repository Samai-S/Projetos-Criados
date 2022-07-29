#include <iostream>
#include <string>
#include "structs.cpp"

#include <bits/stdc++.h>
using namespace std;


Tupla TrataMatriz(string *matriz, int **visitado, Tupla T, Tupla Posicao, char CiclistaNome)
{

    for (int i = 0; i < T.valor1; i++)
    {
        for (int j = 0; j < T.valor2; j++)
        {
            if (matriz[i][j] == '-')
                visitado[i][j] = 1;
            else
                visitado[i][j] = 0;

            if (matriz[i][j] == CiclistaNome)
            {
                Posicao.valor1 = i;
                Posicao.valor2 = j;
            }
        }
    }

    return Posicao;
}

int CalculaDistancia(string *matriz, Tupla T, char CiclistaNome, char bicicleta)
{
    Coordenadas Ciclista;
    Ciclista.linha = 0;
    Ciclista.coluna = 0;
    Ciclista.distancia = 0;
    
    int **visitado;

    visitado = new int *[T.valor1];
    for (int i = 0; i < T.valor1; i++)
        visitado[i] = new int[T.valor2];

    Tupla Posicao;

    Posicao = TrataMatriz(matriz, visitado, T, Posicao, CiclistaNome);

    Ciclista.linha = Posicao.valor1;
    Ciclista.coluna = Posicao.valor2;

    queue<Coordenadas> fila;

    fila.push(Ciclista);

    visitado[Ciclista.linha][Ciclista.coluna] = 1;

    while (!fila.empty())
    {
        Coordenadas filacopia = fila.front();
        fila.pop();

        if (matriz[filacopia.linha][filacopia.coluna] == bicicleta)
            return filacopia.distancia;

        if (filacopia.linha - 1 >= 0 && visitado[filacopia.linha - 1][filacopia.coluna] == 0)
        {
            Coordenada novo;
            novo.coluna = filacopia.coluna;
            novo.linha = filacopia.linha - 1;
            novo.distancia = filacopia.distancia + 1;

            fila.push(novo);
            visitado[filacopia.linha - 1][filacopia.coluna] = 1;
        }

        if (filacopia.linha + 1 < T.valor1 && visitado[filacopia.linha + 1][filacopia.coluna] == 0)
        {
            Coordenada novo;
            novo.coluna = filacopia.coluna;
            novo.linha = filacopia.linha + 1;
            novo.distancia = filacopia.distancia + 1;

            fila.push(novo);
            visitado[filacopia.linha + 1][filacopia.coluna] = 1;
        }

        if (filacopia.coluna - 1 >= 0 && visitado[filacopia.linha][filacopia.coluna - 1] == 0)
        {
            Coordenada novo;
            novo.coluna = filacopia.coluna - 1;
            novo.linha = filacopia.linha;
            novo.distancia = filacopia.distancia + 1;

            fila.push(novo);
            visitado[filacopia.linha][filacopia.coluna - 1] = 1;
        }

        if (filacopia.coluna + 1 < T.valor2 && visitado[filacopia.linha][filacopia.coluna + 1] == 0)
        {
            Coordenada novo;
            novo.coluna = filacopia.coluna + 1;
            novo.linha = filacopia.linha;
            novo.distancia = filacopia.distancia + 1;

            fila.push(novo);
            visitado[filacopia.linha][filacopia.coluna + 1] = 1;
        }
    }
    return -1;
}
