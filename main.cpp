#include "Game.h"
#include <SFML/System.hpp>
#include <iostream>
#include <cstdio>

void interpreter(TaskManager *);

int main()
{
    Game g;
    sf::Thread thread(&Game::start, &g);
    thread.launch();

    TaskManager * tm = g.getTaskManager();

    sf::Thread thread2(&interpreter, tm);
    thread2.launch();
}

void interpreter(TaskManager * tm) {
    std::string command;
    while (true)
    {
        std::cout << " >>> ";
        getline(std::cin, command);

        if (command == "idź 10 w lewo") if (!tm->move(-10, 0)) std::cout << tm->getError().toAnsiString() << std::endl;
        if (command == "idź do 0 0") tm->goCoordinates(-10, -10);
        if (command == "rozłącz") tm->quit();
        //...
    }
}
