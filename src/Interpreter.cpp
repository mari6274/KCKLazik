#include "Interpreter.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include <string>
Interpreter::Interpreter()
{

}

Interpreter::~Interpreter()
{
    //dtor
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

char * znajdzslowo_klucz(char slowo[])
{
    char * spr1="impt:sg:sec:imperf";
    char * spr2="impt:sg:sec:perf";
    char * word;
    InterpMorf *wyraz;
    wyraz=morfeusz_analyse(slowo);
    word=(wyraz->interp);
    char * klucz =(wyraz->haslo);
    if ( strcmp(word,spr1)==0 || strcmp(word,spr2)==0)
    {
        return klucz;
    }
    else
        return "null";

}

void Interpreter::interpretuj()
{
    char * klucz;
    char * Gklucz="null";
    std::string polecenie;
    std::cout << "wpisz polecenie: ";
    getline(std::cin, polecenie);
    std::vector<std::string> v;
    split(polecenie, ' ', v);

    for (std::string x : v)
    {
        char * cstr = new char[x.length()+1];
        strcpy(cstr, x.c_str());
        InterpMorf *wyraz;
        wyraz=morfeusz_analyse(cstr);
        std::cout << wyraz->forma << " " << wyraz->haslo  << " " << wyraz->interp << std::endl;
        klucz=znajdzslowo_klucz(cstr);
        if (strcmp(klucz,"null")!=0)
        {
             Gklucz=klucz;
        }
    }
     std::cout << Gklucz;
}
