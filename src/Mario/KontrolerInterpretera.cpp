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
    sf::String command = tm->readCommand();
    std::vector<std::string> komendy = Helper::dzielNaZdania(command);
    for (std::string komenda : komendy)
    {
        wykonajKomende(komenda);
    }
}

void KontrolerInterpretera::wykonajKomende(std::string komenda)
{
    std::string wynik = interpreter.interpretuj(komenda);
    if (wynik == "obroc")
        if (!tm->move(10,0))
            console->setOutput(tm->getError().toAnsiString());
}

} // namespace Mario

