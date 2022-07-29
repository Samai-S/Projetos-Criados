#include <string>

using namespace std;

struct Node
//struct auxiliar
//info = string conteudo, node é um apontador, nivel é a profundidade da url,pos é a posicao na qual foi conhecida, id é o id vinculado ao Host
{
    string info;
    Node *next;
    int nivel;
    int pos;
    int id;
};

#ifndef URL_H
#define URL_H

class URL
//class URL na qual é uma lista para execucao do programa
{
public:
    URL();
    ~URL();
    bool isEmpty();//verifica se e vazia
    void print();//imprime url
    void SetItem(string, int, int);//insere item na fila
    void imprimeID(int, string);//imprime por id;
    void imprimePOS(int);//imprime pela ordem de conhecimento
    void limpaID(int);//limpa id
    bool existe(string, int);//retorna se o id existe
    void VER_HOST(int, string);//ver todos hosts de um id
    void limpaQuantidade(int, int, string);//limpa uma quantidade determinada de URLS
    void EscalonaQuantidade(int, int, string);//Escalona uma quantidade determinada de URLS
    void imprime();
    void clear();

private:
    Node *head;
    int tamanho;
};

#endif