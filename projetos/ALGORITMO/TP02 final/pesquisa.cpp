#include<iostream>


using namespace std;

typedef struct tupla
{
    int valor1;
    int valor2;

}tupla;

int EncontraMin(int **matriz, int n_cidades)
//encontra o menor caminho do grafo
{
    int i, j, min = 99999999, I_backup, J_backup;
    
    //loop para achar o menor valor
    for (i = 0; i < n_cidades; i++)
    {
        for (j = 0; j < n_cidades; j++)
        {
            if (matriz[i][j] != -1 && matriz[i][j] < min)
            {
                min = matriz[i][j];
                I_backup = i;
                J_backup = j;
            }
        }
    }
    matriz[I_backup][J_backup] = -1;

    //retorna minimo
    return min;
}


bool EncontraCaminho(int **matriz, int inicial, int final, int n_cidades, int n_caminhos)
{
    int n_usados = 0, i = 0, j = 0, count = 0,i_anterior=-1,valor=0;
    bool usado[n_cidades];

    int sequencia[n_cidades];

    
    for (i = 0; i < n_cidades; i++)
    {
        usado[i] = false;//inicializa o vertice para saber se foi visitado ou nao
    }

    i = inicial;
    usado[inicial] = true;
    sequencia[valor]=i;    
    j=0;
    while (n_usados < n_cidades)//loop enquanto o numero de vertices usados seja menor que cidades
    {
        
        if (matriz[i][j] != -1 && j>=0 && n_cidades>j)// se o caminho for possivel e numero cidades>j>0
        {
            
            
            if (usado[j] == false)//se o caminho nao foi visitado
            {
                count++;
                valor++;

                if (valor>=n_cidades)
                {
                    break;
                }

                if (j == final)
                {
                    return true;
                }
                sequencia[valor]=i;
                
                i = j;

                usado[j] = true;
                n_usados++;
                j = -1;
            }

        }

        else if (matriz[i][j] == -1 && j + 1 >= n_cidades)
        //se a ultima posição da matriz é igual a -1 volta uma posiçao no heap
        {
            
            valor--;

            if (valor == -1)
            {
                
                break;
            }

            
            i = sequencia[valor+1];
            
            j = -1;
        }

        j++;
        


        if (count == n_caminhos||j>=n_caminhos)//se percorreu todos os caminhos do grafo, retorna
        {
            break;
        }
    }
   

    return false;
}







void EncontraMaiorCaminho(int **matriz, int inicial, int final, int n_cidades, int n_caminhos)
{
    int i=0, j=0, minimo = 0;
    int **matrizaux;

    matrizaux = new int *[n_cidades];

    for (i = 0; i < n_cidades; i++)
    {
        matrizaux[i] = new int[n_cidades];
    }

    for (i = 0; i < n_cidades; i++)
    {
        for (j = 0; j < n_cidades; j++)
        {
            matrizaux[i][j] = matriz[i][j];
        }
    }

    //itera sobre os caminhos de menores pesos e vê se há caminho disponivel
    while (EncontraCaminho(matrizaux, inicial, final, n_cidades, n_caminhos))
    {
        minimo = EncontraMin(matrizaux, n_cidades);
        
    }

    delete(matrizaux);
    for (i = 0; i < n_cidades; i++)
    {
        delete(matrizaux[i]);
    }
     delete(matrizaux);
    cout << minimo << endl;
}


void pesquisas(int **matriz,int n_cidades,int caminhos,int consultas)
{
    int count=0;

    tupla vetorconsultas[consultas];

    
    while(count<consultas)
    {
       cin>>vetorconsultas[count].valor1;
       cin>>vetorconsultas[count].valor2;
       count++;
    }

    count=0;
    while(count<consultas)
    {
        
       EncontraMaiorCaminho(matriz,vetorconsultas[count].valor1-1,vetorconsultas[count].valor2-1, n_cidades, caminhos);
       count++;
    }


}