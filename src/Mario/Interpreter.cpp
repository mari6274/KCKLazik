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

        InterpMorf * imtable;
        imtable = morfeusz_analyse(cstr);

        for (int i = 0; imtable[i].p != -1; ++i)
        {
            if (imtable[i].haslo != NULL) {
                std::string leksem(imtable[i].haslo);
                output.insert(leksem);
            }
        }

    }

    //morfeusz debug
    std::cout << std::endl << "==============" << std::endl;
    for (std::string leksem : output)
    {
        std::cout << leksem << std::endl;

    }
    std::cout << "==============" << std::endl;
    //morfeusz debug

    return output;
}

InterpResult Interpreter::interpretuj(std::string in)
{
    ir.command = "";
    leksemy = morfeusz(in);

    if (przesuwanieO()) return ir;

    return ir;
}

bool Interpreter::przesuwanieO()
{

    if (
        leksemy.find("iść") != leksemy.end() &&
        leksemy.find("o") != leksemy.end()
        )
    {
        ir.command = "move";
        ir.dataArray[0] = 5;
        ir.dataArray[1] = 0;
        return true;
    }
    return false;
}

bool Interpreter::przesuwanieDo()
{

}

bool Interpreter::przesuwanieAuto()
{

}

bool Interpreter::obracanie()
{

}

} // namespace Mario
