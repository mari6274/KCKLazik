#include "Mario/Interpreter.h"

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

        output.insert(im->haslo);
    }

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
