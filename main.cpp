#include "Game.h"
#include <SFML/System.hpp>
#include <iostream>
#include <cstdio>
#include<fstream>
#include <vector>
#include<map>
#include "Console.h"
#include"Interpreter.h"
#define DEBUG true
#include "Aiml.h"
#include "Helper.h"

void interpreter(Game *);

using namespace std;
int main()
{

    Game * g = new Game();
    sf::Thread thread(&Game::start, g);

    thread.launch();

    sf::Thread thread2(&interpreter, g);
    thread2.launch();
}

void interpreter(Game * g) {
    sf::String command;
    TaskManager * tm = g->getTaskManager();
    Console * console = g->getConsole();
    Interpreter interpreter(tm, console);
    interpreter.interpretuj();


//    while (true)
//    {
//        std::vector<sf::String> commands;
//        commands.push_back(L"idź 10 w lewo");
//        commands.push_back(L"idź 10 w prawo");
//        commands.push_back(L"idź 10 w górę");
//        commands.push_back(L"idź 10 w dół");
//        commands.push_back(L"idź do 0 0");
//        commands.push_back(L"auto 0 0");
//        commands.push_back(L"rozłącz");
//
//        command = tm->readCommand();
//
//        console->setOutput(Helper::stringZPlikuNaSfString(znajdowanie(command)));
//        if (command == commands[0]) if (!tm->move(-10, 0)) //std::cout << tm->getError().toAnsiString() << std::endl;
//            console->setOutput(tm->getError());
//        if (command == commands[1]) if (!tm->move(10, 0)) //std::cout << tm->getError().toAnsiString() << std::endl;
//            console->setOutput(tm->getError());
//        if (command == commands[2]) if (!tm->move(0, -10)) //std::cout << tm->getError().toAnsiString() << std::endl;
//            console->setOutput(tm->getError());
//        if (command == commands[3]) if (!tm->move(0, 10)) //std::cout << tm->getError().toAnsiString() << std::endl;
//            console->setOutput(tm->getError());
//        if (command == commands[4]) if (!tm->goCoordinates(0, 0)) //std::cout << tm->getError().toAnsiString() << std::endl;
//            console->setOutput(tm->getError());
//        if (command == commands[5]) if (!tm->goCoordinates(0, 0, true)) //std::cout << tm->getError().toAnsiString() << std::endl;
//            console->setOutput(tm->getError());
//        if (command == commands[6]) tm->quit();
//        //...
//    }
}
