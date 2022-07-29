#include <iostream>
#include <fstream>
#include "HOST.hpp"
#include "URL.hpp"

using namespace std;

URL::URL()
//construtor URL
{
    head = NULL;
    tamanho = 0;
}

URL::~URL()
//destrutor URL
{
    Node *tempPtr;
    while (head != NULL)
    {
        tempPtr = head;
        head = head->next;
        delete tempPtr;
    }
}

bool URL::isEmpty()
//verifica se a URL está vazia
{

    return head == NULL;
}

void URL::SetItem(string S, int nv, int i)
//recebe uma string com nome da URL, nivel e id na qual sera inserida
//insere a URL na lista
{
    tamanho++;
    Node *newNode;
    Node *p;
    p = new Node;
    newNode = new Node;
    newNode->info = S;
    newNode->nivel = nv;
    newNode->id = i;
    newNode->pos = tamanho;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }

    else if (head->id > newNode->id)
    {
        p = head;
        head = newNode;
        head->next = p;
    }

    else if (head->id == newNode->id && head->nivel > newNode->nivel)
    {
        p = head;
        head = newNode;
        head->next = p;
    }

    else
    {

        Node *aux;
        aux = new Node;
        aux = head;

        while (aux != NULL)
        {

            if (aux->next != NULL)
            {
                if (aux->next->id > newNode->id)
                {

                    if (aux->next->nivel > newNode->nivel)
                    {
                        //cout << " rodou" << endl;
                        newNode->next = aux->next;
                        aux->next = newNode;
                        break;
                    }

                    if (aux->nivel == newNode->nivel && aux->next->nivel < newNode->nivel)
                    {
                        newNode->next = aux->next;
                        aux->next = newNode;
                        break;
                    }
                }
                if (aux->next->id == newNode->id)
                {

                    if (aux->next->nivel > newNode->nivel)
                    {
                        //cout << " rodou" << endl;
                        newNode->next = aux->next;
                        aux->next = newNode;
                        break;
                    }

                    if (aux->nivel == newNode->nivel && aux->next->nivel < newNode->nivel)
                    {
                        newNode->next = aux->next;
                        aux->next = newNode;
                        break;
                    }
                }
            }

            if (aux->next == NULL)
            {
                newNode->next = aux->next;
                aux->next = newNode;
                break;
            }

            aux = aux->next;
        }
    }
}

void URL::imprimeID(int id, string s)
//recebe um id e uma string para abrir arquivo
//imprime todos hosts de uma id
{
    ofstream ofs(s, ios::app);
    Node *aux;
    aux = new Node;
    aux = head;

    while (aux != NULL)
    {

        if (aux->id == id)
        {
            ofs << aux->info << endl;
        }
        aux = aux->next;
    }
    ofs.close();
}

void URL::imprime()
//imprime tudo
{

    Node *aux;
    aux = new Node;
    aux = head;

    while (aux != NULL)
    {
        if (aux->nivel != 0)
            cout << aux->info << endl;

        aux = aux->next;
    }
}

void URL::limpaID(int i)
//recebe um id de HOST no qual sera esvaziado
{

    Node *aux;
    aux = new Node;
    aux = head;

    while (aux != NULL)
    {

        if (aux->id == i)
        {
            aux->id = -1;
        }
        aux = aux->next;
    }
}

void URL::VER_HOST(int i, string s)
//ve todos os URLS dos hosts
{
    ofstream ofs(s, ios::app);
    Node *aux;
    aux = new Node;
    aux = head;

    while (aux != NULL)
    {

        if (aux->id == i && aux->nivel > 0)
        {
            ofs << aux->info << endl;
        }
        aux = aux->next;
    }
}

void URL::limpaQuantidade(int id, int quantidade, string s)
//Limpa uma quantidade determinada de URLS de uma id
{
    ofstream ofs(s, ios::app);
    Node *aux;
    aux = new Node;
    aux = head;
    int testa = 0;

    while (aux != NULL)
    {

        if (aux->id == id)
        {
            ofs << aux->info << endl;
            aux->id = -1;
            testa++;
        }

        if (testa == quantidade)
            break;

        aux = aux->next;
    }
}

void URL::imprimePOS(int i)
//imprime por ordem na qual foi conhecida
{

    Node *aux;
    aux = new Node;
    aux = head;
    int posicao = 1;

    while (aux != NULL)
    {
        if (aux->id == i && aux->pos == posicao)
        {
            posicao++;
            cout << aux->info << endl;

            aux = head;
        }

        aux = aux->next;
    }
}

void URL::clear()
//Limpa a fila
{

    while (head->next != NULL)
    {
        Node *aux;
        aux = new Node;

        aux = head->next;
        head->next = aux->next;

        delete aux;
    }

    delete head;
}

void URL::EscalonaQuantidade(int quantidade, int size, string s)
//Escala uma certa quantidade de URLS
{
    int i = 0;
    ofstream ofs(s, ios::app);
    Node *aux;
    aux = new Node;
    aux = head;
    int testa = 0;

    while (i < size)
    {
        aux = head;

        while (aux != NULL)
        {
            if (testa == quantidade)
            {
                break;
            }

            if (aux->id == i)
            {
                ofs << aux->info << endl;
                aux->id = -1;
                testa++;
            }

            aux = aux->next;
        }

        i++;
    }
}

bool URL::existe(string s, int i)
//verifica se existe uma URL
{
    Node *aux;
    aux = new Node;
    aux = head;
    int testa = 0;

    while (aux != NULL)
    {

        if (aux->id == i)
        {
            if (s == aux->info)
                return true;
        }

        aux = aux->next;
    }

    return false;
}