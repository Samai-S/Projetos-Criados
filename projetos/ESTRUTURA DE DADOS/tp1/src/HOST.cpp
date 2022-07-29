#include <iostream>
#include "HOST.hpp"
#include <fstream>

using namespace std;

HOST::HOST()
//construtor HOST
{
    front = NULL;
    rear = NULL;
    tamanho = 0;
}

HOST::~HOST()
//destrutor HOST
{
    NodeType *tempPtr;
    while (front != NULL)
    {
        tempPtr = front;
        front = front->next;
        delete tempPtr;
    }

    rear = NULL;
}

bool HOST::isEmpty() const
//Verifica se o Host esta vazio
{
    return (front == NULL);
}

void HOST::print(string s) const
//Recebe uma string com nome de arquivo
//imprime no arquivo todas as Hosts
{
    ofstream ofs(s, ios::app);
    NodeType *tempPtr = front;
    while (tempPtr != NULL)
    {
        ofs << tempPtr->info << endl;
        tempPtr = tempPtr->next;
    }
}

void HOST::SetItem(string S)
//Recebe uma string para ser adicionada á fila
//Insere a string na fila
{
    NodeType *newNode;
    newNode = new NodeType;
    newNode->info = S;
    newNode->escalonada = 0;
    newNode->id = tamanho;
    newNode->next = NULL;
    if (rear == NULL)
        front = newNode;
    else
        rear->next = newNode;
    rear = newNode;

    tamanho++;
}

int HOST::GetID(string s)
//recebe uma string;
//compara com todas Ids para retornar a id que compativel
{
    NodeType *newNode;
    newNode = new NodeType;
    newNode->info = s;

    NodeType *aux;
    aux = new NodeType;
    aux = front;
    while (aux != NULL)
    {

        if (newNode->info == aux->info)
        {
            return aux->id;
        }

        aux = aux->next;
        if (aux == NULL)
        {
            return -1;
        }
    }

    return -1;
}

bool HOST::confereHOST(string s)
//recebe uma string
//retorna se o host existe
{
    NodeType *aux;
    aux = new NodeType;
    aux = front;
    while (aux != NULL)
    {
        if (aux->info == s)
        {
            return true;
        }
        aux = aux->next;
    }
    return false;
}

int HOST::GetTamanho()
//retorna tamanho da fila
{
    return tamanho;
}