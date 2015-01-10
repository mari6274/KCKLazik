#include "Game.h"
#include <SFML/System.hpp>
#include <iostream>
#include <cstdio>
#include<fstream>
#include <vector>
#include<map>
#include "Console.h"
#include"Interpreter.h"
#define DEBUG false
#include <sstream>
#include "Aiml.h"
#include "Helper.h"




void interpreter(Game * g);


int main()
{
//    Interpreter i;
//    i.interpretuj();

    Game * g = new Game();
    sf::Thread thread(&Game::start, g);

    thread.launch();

    sf::Thread thread2(&interpreter, g);
    thread2.launch();
}

void interpreter(Game * g)
{
    sf::String command;
    TaskManager * tm = g->getTaskManager();
    Console * console = g->getConsole();
    while (true)
    {
        std::vector<sf::String> commands;
        commands.push_back(L"idz 10 w lewo");
        commands.push_back(L"idz 10 w prawo");
        commands.push_back(L"idz 10 w gore");
        commands.push_back(L"idz 10 w dol");
        commands.push_back(L"idz do 1 1");
        commands.push_back(L"auto 1 1");
        commands.push_back(L"rozłącz");

        command = tm->readCommand();

        Aiml aiml(console, tm);
       // vector <string> punkty;

     //   punkty=aiml.explode(aiml.weToZrob(command),' ');
       // wypisz(punkty);
     //   tm->goCoordinates(aiml.string_to_int(punkty[1]),aiml.string_to_int(punkty[2]),false);


        console->setOutput(Helper::stringZPlikuNaSfString(aiml.weToZrob(command)));

    //    if (command == commands[0]) if (!tm->move(-10, 0)) //std::cout << tm->getError().toAnsiString() << std::endl;
      //          console->setOutput(tm->getError());
      //if (command == commands[1]) if (!tm->move(10, 0)) //std::cout << tm->getError().toAnsiString() << std::endl;
        //        console->setOutput(tm->getError());
    //    if (command == commands[2]) if (!tm->move(0, -10)) //std::cout << tm->getError().toAnsiString() << std::endl;
      //          console->setOutput(tm->getError());
 //       if (command == commands[3]) if (!tm->move(0, 10)) //std::cout << tm->getError().toAnsiString() << std::endl;
   //             console->setOutput(tm->getError());
     //   if (command == commands[4]) if (!tm->goCoordinates(0, 0)) //std::cout << tm->getError().toAnsiString() << std::endl;
       //         console->setOutput(tm->getError());
   //     if (command == commands[5]) if (!tm->goCoordinates(0, 0, true)) //std::cout << tm->getError().toAnsiString() << std::endl;
     //           console->setOutput(tm->getError());
       // if (command == commands[6]) tm->quit();
        //...
    }
}





