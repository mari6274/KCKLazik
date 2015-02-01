#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Helper.h"
#include <queue>

struct ConsoleHistoryItem
{
    sf::String text;
    sf::Color color;
};

class Console
{
    public:
        Console(sf::RenderWindow * window);
        void draw();
        void setOutputFromKeyboard(sf::String s, bool speech = false);
        void setOutput(std::string s, bool speech = true);
        sf::String getCommand();
        void setCommand(sf::String s);
        sf::String getAndSetLastCommand();
    protected:
    private:
        std::queue<ConsoleHistoryItem> history;
        void updateView();
        sf::String lastCommand;

        sf::RenderWindow * window;
        sf::Font courier;
        sf::Text t1;
        sf::Text t2;
        sf::Text t3;
        sf::Text t4;
        sf::Text prompt;
};

#endif // CONSOLE_H
