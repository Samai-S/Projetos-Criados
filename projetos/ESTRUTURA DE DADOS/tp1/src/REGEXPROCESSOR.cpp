#include <iostream>
#include <regex>
#include "REGEXPROCESSOR.hpp"

using namespace std;

string verifica_host(string link)
//recebe uma string
//retorna uma string processada padronizada
{

    string homePage;
    string URL;

    regex somente_homePage("(http://(.*?)/)");
    smatch match_homePage;
    if (regex_search(link, match_homePage, somente_homePage))
    {
        homePage = match_homePage.str();
    }

    return homePage;
}

bool verifica_URL(string link)
//recebe uma string
//retorna se é uma URL valida
{

    string homePage;
    string URL;

    regex somente_homePage1("(.pdf)");
    smatch match_homePage1;
    if (regex_search(link, match_homePage1, somente_homePage1))
    {
        return false;
    }

    regex somente_homePage2("(.jpg)");
    smatch match_homePage2;
    if (regex_search(link, match_homePage2, somente_homePage2))
    {
        return false;
    }
    regex somente_homePage3("(.gif)");
    smatch match_homePage3;
    if (regex_search(link, match_homePage3, somente_homePage3))
    {
        return false;
    }
    regex somente_homePage4("(.mp3)");
    smatch match_homePage4;
    if (regex_search(link, match_homePage4, somente_homePage4))
    {
        return false;
    }
    regex somente_homePage5("(.avi)");
    smatch match_homePage5;
    if (regex_search(link, match_homePage5, somente_homePage5))
    {
        return false;
    }
    regex somente_homePage6("(.doc)");
    smatch match_homePage6;
    if (regex_search(link, match_homePage6, somente_homePage6))
    {
        return false;
    }

    return true;
}


int processa_niveis(string link)
//recebe string
//processa os niveis de cada string
{

    int counter_niveis = 0;
    string URL;
    regex link_completo("(http://(.*?)|)");
    smatch match_linkURL;
    if (regex_search(link, match_linkURL, link_completo))
    {
        URL = match_linkURL.str();

        for (char &c : URL)
        {
            if (c != '/')
                counter_niveis++;
        }
    }

    return counter_niveis;
}
