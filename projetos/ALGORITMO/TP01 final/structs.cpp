#include<iostream>

using namespace std;

typedef struct Coordenada
{
    int linha;
    int coluna;
    int distancia;

} Coordenadas;

typedef struct Tupla
{
    int valor1;
    int valor2;

} Tupla;

typedef struct Bicicleta 
{
    bool casado;
    char nome;
    int conjuje;

}Bicicleta;

typedef struct Ciclista 
{
    bool casado;
    char nome;
    int conjuje;

}Ciclista;

typedef struct Casamanto
{
    char ciclista;
    char bicicleta;
    int conjuje;

}Casamento;

typedef struct VetorAux
{
    int numero;
    bool usado;
    
}VetorAux;

