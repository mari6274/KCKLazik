#include "Game.h"
#include <SFML/System.hpp>
#include <iostream>
#include <cstdio>
int main()
{
    Game g;
    // g.start();
    sf::Thread thread(&Game::start, &g);
    thread.launch();
    char a;
    while (true)
    {
        std::cin >> a;
        if (a == 'a') g.getTaskManager()->move(-10,0);
        if (a == 'd') g.getTaskManager()->move(10,0);
        if (a == 'w') g.getTaskManager()->move(0,-10);
        if (a == 's') g.getTaskManager()->move(0,10);
    }
}
