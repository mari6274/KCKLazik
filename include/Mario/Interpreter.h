#ifndef MARIO_INTERPRETER_H
#define MARIO_INTERPRETER_H

#include <vector>
#include <string.h>
#include <string>
#include "Helper.h"
#include "morfeusz.h"
#include <set>
#include <ctype.h>
#include <stdlib.h>
#define DEBUG false

namespace Mario {

struct InterpResult
{
    std::string command;
    int dataArray[4];
};

class Interpreter
{
    public:
        static Interpreter & getInstance();
        InterpResult interpretuj(std::string in);
        void setObiekty(std::vector<Object*> v);
        void setPozycjaLazika(sf::Vector2f v);
        void setObrotLazika(int o);
    protected:
    private:
        Interpreter();
        std::set<std::string> morfeusz(std::string in);

        std::vector<Object*> obiekty;
        std::vector<Object*> obiektyWyswietlane;
        void aktualizujWyswietlaneObiekty();

        sf::Vector2f pozycjaLazika;
        int obrotLazika;

        InterpResult ir;
        std::set<std::string> leksemy;
        std::vector<int> liczby;
        bool inLeksemy(std::string s);
        bool anyInLeksemy(std::vector<std::string> tab);
        int objectInLeksemy();

        bool przesuwanieO();
        bool przesuwanieDo();
        bool przesuwanieAuto();
        bool obracanie();
        bool sasiedztwo();
        bool otoczenie();
        bool najblizszyObiekt();
        bool aktualnaPozycja();
        bool kopanie();
        bool exit();

        std::vector<int> wyszukajLiczby(std::string in);
};

} // namespace Mario

#endif // MARIO_INTERPRETER_H
