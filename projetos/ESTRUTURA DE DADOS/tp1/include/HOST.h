#include <string>

using namespace std;

struct NodeType
//struct auxiliar
//string info é onde fica armazenada as informacoes dos HOSTS, next é um ponteiro para o proximo nó, int escalonada valor se o host esta escalonada, id é o id do host
{
    string info;
    NodeType *next;
    int escalonada;
    int id;
};

#ifndef HOST_H
#define HOST_H

class HOST
{
public:
    HOST();
    ~HOST();
    bool isEmpty() const;//verifica se o Host está vazio
    void print(string) const;//imprime
    void SetItem(string);//insere um host na fila
    int GetID(string);//Retorna uma Id de uma determinada string
    bool confereHOST(string);//confere se o host existe
    int GetTamanho();//Retorna o tamanho da fila

private:
    NodeType *front;
    NodeType *rear;
    int tamanho;
};

#endif