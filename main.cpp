#include "Game.h"
#include "TaskManager.h"
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
#include "Mario/KontrolerInterpretera.h"
void interpreter(Game * g)
{
    sf::String command;
    TaskManager * tm = g->getTaskManager();
    Console * console = g->getConsole();
    Aiml aiml(console, tm);

    Mario::KontrolerInterpretera * kontroler = new Mario::KontrolerInterpretera(console, tm);

    while (true)
    {
//        command = tm->readCommand();
//        std::vector<std::string> wyniki = aiml.start(command);
//        for (std::string s : wyniki)
//        {
//            console->setOutput(s);
//        }

        kontroler->interpretuj();
    }
}





