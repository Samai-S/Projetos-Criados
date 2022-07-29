#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "HOST.hpp"
#include "URL.hpp"
#include "REGEXPROCESSOR.hpp"

using namespace std;

//variaveis globais

HOST HOMEPAGE;
URL LINKS;

string processahost(string s)
//Funcao recebe uma string como parâmetro
//Processa as strings de uma forma padrao
//Retorna uma string processada e padronizada

{

    int i = 0, tamanho = 0, pos = 0;
    string j;
    pos = s.size();

    if (pos < 2)
    {
        j = "stop";
    }
    if (pos > 8)
    {
        j = s.substr(7, pos);

        pos = j.find("/");
        j = j.substr(0, pos);

        if (j[0] == 'w' && j[1] == 'w' && j[2] == 'w' && j[3] == '.')
            j = j.substr(4, pos - 1);
    }

    return j;
}

int processanivel(string s)
//recebe uma string como parametro
//processa o nivel de cada string
//retorna o nivel da URL
{
    int i = 0, tamanho = 1, pos = 0, diferenca = 10, pos2 = 0, size = 0;
    string j;
    pos = s.size();

    j = s.substr(7, pos);

    while (diferenca > 0)
    {
        size = j.size();
        if (size <= 1)
        {
            tamanho = tamanho - 1;
            break;
        }

        pos2 = j.find("/");
        if (pos2 == -1)
        {
            break;
        }

        j = j.substr(pos2 + 1, pos);

        tamanho++;
    }

    return tamanho;
}

string processaURL(string s)
//Recebe uma string
//Processa as URL para tamanho padrao
//Retorna URL processada e padronizada
{
    int pos;
    pos = s.size();

    if (s[pos - 1] == '/')
        s = s.substr(0, pos - 1);

    if (s[7] == 'w' && s[8] == 'w' && s[9] == 'w' && s[10] == '.')
        s.erase(7, 4);

    return s;
}

void ADD_URL(string s)
//Recebe uma string
//Adiciona uma URL à fila
{
    string host;
    int nivel = 0;
    int id;

    if (verifica_URL(s))
    {
        host = verifica_host(s);

        host = processahost(host);

        if (host != "stop")
        {
            if (!HOMEPAGE.confereHOST(host))
            {
                HOMEPAGE.SetItem(host);
            }

            id = HOMEPAGE.GetID(host);
            nivel = processanivel(s);
            s = processaURL(s);
            if (!LINKS.existe(s, id))
                LINKS.SetItem(s, nivel, id);
            //cout << s << "  " << host << " id: " << id << " nivel: " << nivel << endl;
        }
    }
}

void ESCALONA_TUDO(string s)
//Recebe uma string;
//Escalona as URL;
{
    int i = 0, j = 0;
    i = HOMEPAGE.GetTamanho();

    while (j <= i)
    {
        LINKS.imprimeID(j, s);
        LINKS.limpaID(j);
        j++;
    }
}

void LISTA_HOSTS(string s)
//Recebe uma string
//Imprime Lista de Hosts
{
    HOMEPAGE.print(s);
}

void LIMPA_TUDO()
//Limpa todos os Hosts
{
    HOMEPAGE.~HOST();
    LINKS.~URL();
}

void LIMPA_HOST(string s)
//Recebe uma string
//Limpa um Determinado Host
{
    int id;
    id = HOMEPAGE.GetID(s);

    LINKS.limpaID(id);
}

void VER_HOST(string s, string j)
//Recebe duas duas strings
//Ver todos as URLS de um determinado Host
{
    int id;
    id = HOMEPAGE.GetID(s);

    LINKS.imprimeID(id, j);
}

void ESCALONA_HOST(string S, int quantidada, string s)
//Recebe duas stirngs e um inteiro
//Escalona um determinado Host
{
    int id;
    id = HOMEPAGE.GetID(S);

    LINKS.limpaQuantidade(id, quantidada, s);
}

void ESCALONA(int quantidade, string s)
//Recebe um int e uma string;
//Escalona uma determinada quantidade de URLS
{
    int i;

    i = HOMEPAGE.GetTamanho();

    LINKS.EscalonaQuantidade(quantidade, i, s);
}

int main()
//Main na qual todos as funçoes sao executadas

{
    //variaveis para execucao da main
    int quantidade = 0, execucoes = 0, pos = 0;
    string file_name;
    string filehelp1;
    string filehelp2;
    int filehelpos1, filehelpos2;
    string line;
    string function;
    string substring;
    string aux;
    string aux1;
    string aux2;
    stringstream str;
    string arquivo;
    //recebe nome do arquivo
    cin >> file_name;
    filehelpos1 = file_name.find(".");
    filehelp2 = "-out.txt";
    arquivo = file_name;
    arquivo.erase(filehelpos1, arquivo.back());

    arquivo = arquivo + filehelp2;

    remove(arquivo.c_str());
    //cria arquivo para ser impresso
    ofstream ofs(arquivo, ios::app);

    ifstream ifs(file_name);
    //while do getline
    while (getline(ifs, line))
    {
        str.clear();
        pos = line.find(" ");
        if (pos != -1)
        {
            function = line.substr(0, pos - 1);
        }
        else
            function = line;
        substring = line;

        //verificacao se a funcao necessaria

        if (function == "ADD_URL")
        {

            str << line;
            str >> aux >> aux1;

            quantidade = stoi(aux1);

            execucoes = 0;
            while (execucoes < quantidade)
            {
                getline(ifs, line);
                ADD_URL(line);
                execucoes++;
            }
        }

        if (function == "ESCALONA_TUDO")
        { //certo
            ESCALONA_TUDO(arquivo);
        }

        if (function == "ESCALON")
        { //certo
            str << line;
            str >> aux >> aux1;
            quantidade = stoi(aux1);
            ESCALONA(quantidade, arquivo);
        }

        if (function == "ESCALONA_HOS") //certo
        {

            str << line;
            str >> aux >> aux1 >> aux2;

            quantidade = stoi(aux2);

            ESCALONA_HOST(aux1, quantidade, arquivo);
        }
        if (function == "VER_HOS") //certo
        {

            str << line;
            str >> aux >> aux1;
            ;
            VER_HOST(aux1, arquivo);
        }
        if (function == "LISTA_HOSTS") //certo
        {

            LISTA_HOSTS(arquivo);
        }
        if (function == "LIMPA_HOST")
        {

            str << line;
            str >> aux;
            LIMPA_HOST(aux);
        }
        if (function == "LIMPA_TUDO") //certo
        {

            LIMPA_TUDO();
        }

        pos = -1;
    }
    ofs.close();
    ifs.close();
    return 0;

}
