#include <iostream>
#include <string>
#include "casamentoestavel.cpp"


using namespace std;

void preenchematriz(string *matriz, int M)
{
    int i = 0;
    do
    {
        cin >> matriz[i];
        i++;
    } while (i < M);
}

void ranking(int **Rank, int M)
{
    int i, j, aux, indice, Max;

    int matrixAux[M][M];
    

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            cin >> matrixAux[i][j];
        }
    }
    
    for (i = 0; i < M; i++)
    {

        for (j = 0; j < M; j++)
        {
            aux = 0;
            Max=-1;

            while (aux < M)
            {
                if (matrixAux[i][aux] > Max)
                {
                    Max = matrixAux[i][aux];
                    indice = aux;
                }
                aux++;
            }

            Rank[i][j] = indice+1;
            matrixAux[i][indice] = -1;
        }
    }

}

main()
{
    int M, N, NumeroVisitantes;

    cin >> NumeroVisitantes >> M >> N;

    string matriz[M];

    int **Rank;

    Rank = new int *[NumeroVisitantes];

    for (int i = 0; i < NumeroVisitantes; i++)
    {
        Rank[i] = new int[NumeroVisitantes];
    }
    Tupla T;
    T.valor1 = M;
    T.valor2 = N;
    preenchematriz(matriz, M);
    ranking(Rank, NumeroVisitantes);

    CasamentoEstavel(Rank, NumeroVisitantes, matriz, T);
}