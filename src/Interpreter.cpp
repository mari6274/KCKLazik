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

void Interpreter::interpretuj()
{
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
        std::cout << wyraz->forma << " " << wyraz->haslo << std::endl;
    }


}
