#include <iostream>
#include "distancia.cpp"

using namespace std;

void CasamentoEstavel(int **Rank, int M, string *matriz,Tupla DimensaoMatriz)
{
    int i = 0, j = 0, distanciaA, distanciaB;
    
    Ciclista ciclista[M];
    Bicicleta bicicleta[M];
    Casamanto CasamentoCiClista[M];
    Casamanto CasamentoBicicleta[M];


    for (i = 0; i < M; i++)
    {
        ciclista[i].nome = i + 97;
        ciclista[i].casado = 0;
    }

    for (i = 0; i < M; i++)
    {
        bicicleta[i].nome = i+48;
        bicicleta[i].casado = 0;
        bicicleta[i].conjuje=-1;
    }

    
    for (i = 0; i < M; i++)
    {

        for (j = 0; j < M; j++)
        {
            if (ciclista[i].casado == 1)
            {
                break;
            }
            if (ciclista[i].casado == 0)
            {
                if (bicicleta[Rank[i][j]-1].casado == 0  )
                {
                    
                    CasamentoCiClista[i].bicicleta = bicicleta[Rank[i][j]-1].nome;
                    CasamentoCiClista[i].ciclista = ciclista[i].nome;
                    CasamentoCiClista[i].conjuje = Rank[i][j]-1;

                    ciclista[i].conjuje=Rank[i][j]-1;
                    bicicleta[Rank[i][j]-1].conjuje=i;
                    bicicleta[Rank[i][j]-1].casado = 1;
                    ciclista[i].casado = 1;

                }

                if (bicicleta[Rank[i][j]-1].casado == 1)
                {
                    
                    
                    distanciaA = CalculaDistancia(matriz, DimensaoMatriz, ciclista[bicicleta[Rank[i][j]-1].conjuje].nome, bicicleta[Rank[i][j]-1].nome);
                    distanciaB = CalculaDistancia(matriz, DimensaoMatriz, ciclista[i].nome, bicicleta[Rank[i][j]-1].nome);
                    
                    if(ciclista[i].nome=='h')
                    {
                        cout<<CasamentoBicicleta[Rank[i][j]-1].ciclista<<" "<<CasamentoBicicleta[Rank[i][j]-1].bicicleta<<endl;
                        cout<<distanciaA<<" "<<distanciaB<<" "<<ciclista[i].nome<<" "<<bicicleta[Rank[i][j]-1].nome<<endl;


                    }

                    if (distanciaB < distanciaA)
                    {
                        
                        ciclista[bicicleta[Rank[i][j]-1].conjuje].casado=0;

                        CasamentoCiClista[i].bicicleta = bicicleta[Rank[i][j]-1].nome;
                        CasamentoCiClista[i].ciclista = ciclista[i].nome;
                        CasamentoCiClista[i].conjuje = Rank[i][j]-1;

                        ciclista[i].conjuje=Rank[i][j]-1;
                        bicicleta[Rank[i][j]-1].conjuje=i;
                        bicicleta[Rank[i][j]-1].casado = 1;
                        ciclista[i].casado = 1;

                        i = -1;
                        break;
                        
                }
            }
        }
    }
  
   cout<<endl;

    for(i=0;i<M;i++)
        cout<<CasamentoCiClista[i].ciclista<<" "<<CasamentoCiClista[i].bicicleta<<endl;
}