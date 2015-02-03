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
    ir.command = "Nie rozpoznano komendy";
    leksemy = morfeusz(in);
    liczby = wyszukajLiczby(in);

    if (najblizszyObiekt()) return ir;
    if (przesuwanieAuto()) return ir;
    if (przesuwanieDo()) return ir;
    if (przesuwanieO()) return ir;
    if (obracanie()) return ir;
    if (sasiedztwo()) return ir;
    if (otoczenie()) return ir;
    if (aktualnaPozycja()) return ir;
    if (exit()) return ir;

    return ir;
}

bool Interpreter::inLeksemy(std::string s)
{
    return leksemy.find(s) != leksemy.end();
}

bool Interpreter::anyInLeksemy(std::vector<std::string> tab)
{
    for (std::string s : tab)
    {
        if (inLeksemy(s)) return true;
    }
    return false;
}

int Interpreter::objectInLeksemy()
{
    std::vector<Object *> znalezione;
    //TODO ma wyszukiwać najbliższy
    for (int i = 0 ; i < obiekty.size(); ++i)
    {
        std::string name = obiekty[i]->getName();
        if (inLeksemy(name)) {
            znalezione.push_back(obiekty[i]);
        }
    }

    Object * o = Helper::minimum(znalezione, pozycjaLazika);
    for (int i = 0; i < obiekty.size(); ++i)
    {
        if (o == obiekty[i]) return i;
    }

    return -1;
}

bool Interpreter::przesuwanieO()
{
    std::vector<std::string> tab = {
        "iść",
        "przesunąć",
        "jechać"
    };

    std::vector<std::string> left = {
        "lewo",
        "zachód"
    };

    std::vector<std::string> right = {
        "prawo",
        "wchód"
    };

    std::vector<std::string> up = {
        "góra",
        "północ"
    };

    std::vector<std::string> down = {
        "dół",
        "dołu",
        "południe"
    };

    if (
        anyInLeksemy(tab)
        )
    {
        ir.command = "move";

        if (liczby.size() != 1) {
            ir.command = "Błędna liczba parametrów";
            return true;
        }

        if (anyInLeksemy(left)) {
            ir.dataArray[0] = -1*liczby[0];
            ir.dataArray[1] = 0;
        }
        else if (anyInLeksemy(right)) {
            ir.dataArray[0] = liczby[0];
            ir.dataArray[1] = 0;
        }
        else if (anyInLeksemy(up)) {
            ir.dataArray[0] = 0;
            ir.dataArray[1] = -1*liczby[0];
        }
        else if (anyInLeksemy(down)) {
            ir.dataArray[0] = 0;
            ir.dataArray[1] = liczby[0];
        }
        else {
            ir.command = "Nie określono kierunku lub błędnie określony";
        }

        return true;
    }

    return false;
}

bool Interpreter::przesuwanieDo()
{
    std::vector<std::string> tab = {
        "iść",
        "przesunąć",
        "jechać"
    };

    if (
        anyInLeksemy(tab) &&
        inLeksemy("do")
        )
    {
        if (liczby.size() == 2) {
            ir.command = "go";
            ir.dataArray[0] = liczby[0];
            ir.dataArray[1] = liczby[1];
        }
        else if (liczby.size() == 1) {
            int liczba = liczby[0];
            if (liczba-1 < obiekty.size()) {
                ir.command = "go";
                int x = obiekty[liczba-1]->getPosition().x/50;
                int y = obiekty[liczba-1]->getPosition().y/50;
                ir.dataArray[0] = x;
                ir.dataArray[1] = y;
            } else {
                ir.command = "Błędna liczba współrzędnych lub błędny numer obiektu";
            }
        }
        else {
            ir.command = "Błędna liczba współrzędnych";
        }

        return true;
    }
    return false;
}

bool Interpreter::przesuwanieAuto()
{
    std::vector<std::string> tab = {
        "znaleźć",
        "wyszukać",
        "szukać",
        "poszukać",
        "automat",
        "automatycznie",
        "auto",
        "wyznaczyć",
        "wyznaczać"
    };

    if (
        anyInLeksemy(tab) &&
        inLeksemy("do")
        )
    {
        if (liczby.size() == 2) {
            ir.command = "go auto";
            ir.dataArray[0] = liczby[0];
            ir.dataArray[1] = liczby[1];
        } else {
            ir.command = "Błędna liczba współrzędnych";
        }

        return true;
    }
    return false;
}

bool Interpreter::obracanie()
{
    std::vector<std::string> tab = {
        "obracać",
        "obrócić",
        "odwrócić",
        "zwrócić",
        "skręcić",
        "skręcać",
        "zakręcać",
        "odwracać",
        "zwracać"
    };

    std::vector<std::string> left = {
        "lewo",
        "zachód"
    };

    std::vector<std::string> right = {
        "prawo",
        "wchód"
    };

    std::vector<std::string> up = {
        "góra",
        "północ"
    };

    std::vector<std::string> down = {
        "dół",
        "dołu",
        "południe"
    };

    if (
        anyInLeksemy(tab)
        )
    {
        ir.command = "rotate";

        if (anyInLeksemy(left)) {
            ir.dataArray[0] = 270;
        }
        else if (anyInLeksemy(right)) {
            ir.dataArray[0] = 90;
        }
        else if (anyInLeksemy(up)) {
            ir.dataArray[0] = 0;
        }
        else if (anyInLeksemy(down)) {
            ir.dataArray[0] = 180;
        }
        else {
            ir.command = "Nie określono kierunku lub błędnie określony";
        }

        return true;
    }
    return false;
}

bool Interpreter::sasiedztwo()
{
    std::vector<std::string> tab = {
        "opisać",
        "opisywać",
        "wymienić",
        "wynieniać"
    };

    std::vector<std::string> tab2 = {
        "sąsiad",
        "sąsiedni",
        "sąsiadujący",
        "sąsiedztwo",
        "sąsiadować",
        "obok",
        "blisko"
    };

    if (
        anyInLeksemy(tab) &&
        anyInLeksemy(tab2)
        )
    {
        ir.command = "neighbors";
        return true;
    }
    return false;
}

bool Interpreter::aktualnaPozycja()
{
    std::vector<std::string> tab = {
        "aktualny",
        "łazik",
        "swój"
    };

    std::vector<std::string> tab2 = {
        "pozycja",
        "koordynata",
        "współrzędna"
    };

    if (
        anyInLeksemy(tab) &&
        anyInLeksemy(tab2)
        )
    {
        ir.command = "getPosition";
        return true;
    }

    return false;
}

bool Interpreter::exit()
{
    std::vector<std::string> tab = {
        "wyjście",
        "wychodzić",
        "wyłączyć",
        "rozłączyć",
        "wyjść",
        "opuścić"
    };

    if (anyInLeksemy(tab)) {
        ir.command = "exit";
        return true;
    }

    return false;
}

bool Interpreter::otoczenie()
{
    std::vector<std::string> tab = {
        "opisać",
        "wymienić",
        "wskacać"
    };

    std::vector<std::string> tab2 = {
        "otoczenie",
        "środowisko",
        "okolica",
        "pobliże"
    };

    if (
        anyInLeksemy(tab) &&
        anyInLeksemy(tab2)
        )
    {
        ir.command = "local objects";
        return true;
    }

    return false;
}

bool Interpreter::najblizszyObiekt()
{
    std::vector<std::string> tab = {
        "iść",
        "szukać",
        "wyszukać",
        "znaleźć",
        "jechać",
        "przesunąć"
    };

    std::vector<std::string> tab2 = {
        "sąsiad",
        "sąsiedni",
        "sąsiadujący",
        "sąsiedztwo",
        "sąsiadować",
        "obok",
        "bliski",
        "okolica"
    };

    if (
        anyInLeksemy(tab) &&
        anyInLeksemy(tab2)
        )
    {
        int pos = objectInLeksemy();
        if (pos != -1) {
            ir.command = "go near object";
            ir.dataArray[0] = obiekty[pos]->getPosition().x/50;
            ir.dataArray[1] = obiekty[pos]->getPosition().y/50;
        } else {
            ir.command = "Nie znaleziono w pobliżu obiektu o takiej nazwie";
        }

        return true;
    }

    return false;
}

std::vector<int> Interpreter::wyszukajLiczby(std::string in)
{
    std::vector<int> numbers;
    for (int i = 0; i < in.size(); ++i)
    {
        if (isdigit(in[i]) || in[i] == '-')
        {
            std::string temp;
            while (isdigit(in[i]) || in[i] == '-')
            {
                temp += in[i++];
            }
            --i;
            numbers.push_back(atoi(temp.c_str()));
        }
    }
    return numbers;
}

void Interpreter::setObiekty(std::vector<Object*> v)
{
    this->obiekty = v;
}

void Interpreter::setPozycjaLazika(sf::Vector2f v)
{
    this->pozycjaLazika = v;
}


} // namespace Mario
