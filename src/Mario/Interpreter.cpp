#include "Mario/Interpreter.h"
#include <iostream>

namespace Mario {

Interpreter::Interpreter()
{

}

Interpreter & Interpreter::getInstance()
{
    static Interpreter instance;
    return instance;
}

std::set<std::string> Interpreter::morfeusz(std::string in)
{
    std::vector<std::string> words = Helper::explode(in, ' ');
    std::set<std::string> output;
    for (std::string x : words)
    {
        char * cstr = new char[x.length()+1];
        strcpy(cstr, x.c_str());

        InterpMorf * im;
        im = morfeusz_analyse(cstr);

        if (im->haslo != NULL) {
            std::string leksem(im->haslo);
            output.insert(leksem);
        }

    }

    //morfeusz debug
    std::cout << std::endl << "==============" << std::endl;
    for (std::string leksem : output)
    {
        std::cout << leksem << std::endl;

    }
    std::cout << "==============" << std::endl;
    //morfeus debug

    return output;
}

std::string Interpreter::interpretuj(std::string in)
{
    std::set<std::string> leksemy = morfeusz(in);
    if (leksemy.find("iść") != leksemy.end())
    {

    }

    return "obroc";
}

} // namespace Mario
