#include "Mario/KontrolerInterpretera.h"

namespace Mario {

KontrolerInterpretera::KontrolerInterpretera(Console * console, TaskManager * tm)
:
    interpreter(Interpreter::getInstance())
{
    this->console = console;
    this->tm = tm;
}

void KontrolerInterpretera::interpretuj()
{
    sf::String command = tm->readCommand(true);
    std::vector<std::string> komendy = Helper::dzielNaZdania(command);
    for (std::string komenda : komendy)
    {
        wykonajKomende(komenda);
        sf::sleep(sf::seconds(1));
    }
}

void KontrolerInterpretera::wykonajKomende(std::string komenda)
{
    interpreter.setPozycjaLazika(tm->getCoordinates());
    interpreter.setObrotLazika(tm->getRotation());
    interpreter.setObiekty(tm->getLocalObjects(7, false));
    InterpResult wynik = interpreter.interpretuj(komenda);

    if (wynik.command == "move")
    {
        if (!tm->move(wynik.dataArray[0],wynik.dataArray[1]))
        {
            console->setOutput(tm->getError().toAnsiString());
        }
        return;
    }

    if (wynik.command == "go")
    {
        if (!tm->goCoordinates(wynik.dataArray[0],wynik.dataArray[1]))
        {
            console->setOutput(tm->getError().toAnsiString());
        }
        return;
    }

    if (wynik.command == "go auto")
    {
        if (!tm->goCoordinates(wynik.dataArray[0],wynik.dataArray[1], true))
        {
            console->setOutput(tm->getError().toAnsiString());
        }
        return;
    }

    if (wynik.command == "go near object")
    {
        if (!tm->goCoordinates(wynik.dataArray[0],wynik.dataArray[1]))
        {
            console->setOutput(tm->getError().toAnsiString());
        }
        return;
    }

    if (wynik.command == "getPosition")
    {
        sf::Vector2f v = tm->getCoordinates();
        std::stringstream ss;
        std::string x;
        std::string y;
        ss << v.x/50 << " " << v.y/50;
        ss >> x >> y;
        console->setOutput("Aktualna pozycja to: " + x + " " + y);
        return;
    }

    if (wynik.command == "rotate")
    {
        tm->rotate(wynik.dataArray[0]);
        return;
    }

    if (wynik.command == "neighbors")
    {
        interpreter.setObiekty(tm->getNeighbors());
        return;
    }

    if (wynik.command == "local objects")
    {
        interpreter.setObiekty(tm->getLocalObjects(7));
        return;
    }

    if (wynik.command == "kop")
    {
        sf::Vector2f v(wynik.dataArray[0], wynik.dataArray[1]);
        tm->kop(v);
        return;
    }

    if (wynik.command == "exit")
    {
        tm->quit();
        return;
    }

    console->setOutput(wynik.command);
}

} // namespace Mario

