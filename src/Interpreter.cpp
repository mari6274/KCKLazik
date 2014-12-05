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

char * znajdz_slowo_klucz(char slowo[])
{
    InterpMorf *wyraz;
    wyraz=morfeusz_analyse(slowo);
    if ( strcmp((wyraz->interp),"impt:sg:sec:imperf")==0 || strcmp((wyraz->interp),"impt:sg:sec:perf")==0)
    {
        return (wyraz->haslo);
    }
    else
        return "null";

}

void Interpreter::interpretuj()
{
    char * klucz;
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
        klucz=znajdz_slowo_klucz(cstr);
        if ( strcmp("null",klucz)!=0)
             std::cout << klucz << std::endl;
    }
}
