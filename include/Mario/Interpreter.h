#ifndef MARIO_INTERPRETER_H
#define MARIO_INTERPRETER_H

#include <vector>
#include <string.h>
#include <string>
#include "Helper.h"
#include "morfeusz.h"
#include <set>
#include "Mario/InterpResult.h"
#include <ctype.h>
#include <stdlib.h>

namespace Mario {

class Interpreter
{
    public:
        static Interpreter & getInstance();
        InterpResult interpretuj(std::string in);
    protected:
    private:
        Interpreter();
        std::set<std::string> morfeusz(std::string in);

        InterpResult ir;
        std::set<std::string> leksemy;
        std::vector<int> liczby;
        bool inLeksemy(std::string s);
        bool anyInLeksemy(std::vector<std::string> tab);

        bool przesuwanieO();
        bool przesuwanieDo();
        bool przesuwanieAuto();
        bool obracanie();
        bool sasiedztwo();
        bool aktualnaPozycja();
        bool exit();

        std::vector<int> wyszukajLiczby(std::string in);
};

} // namespace Mario

#endif // MARIO_INTERPRETER_H
