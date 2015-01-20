#include "Console.h"

Console::Console(sf::RenderWindow * window)
{
    this->window = window;

    if (!courier.loadFromFile("courbd.ttf"))
    {
        exit(0);
    }

    t1.setCharacterSize(14);
    t1.setPosition(60, 470);
    t1.setFont(courier);
    t1.setString("");

    t2.setCharacterSize(14);
    t2.setPosition(60, 500);
    t2.setFont(courier);
    t2.setString("");

    t3.setCharacterSize(14);
    t3.setPosition(60, 530);
    t3.setFont(courier);
    t3.setString("");

    t4.setCharacterSize(14);
    t4.setPosition(60, 560);
    t4.setFont(courier);
    t4.setString("");

    prompt.setCharacterSize(14);
    prompt.setPosition(20, 560);
    prompt.setFont(courier);
    prompt.setString(">>>");
}

void Console::draw()
{
    window->draw(t1);
    window->draw(t2);
    window->draw(t3);
    window->draw(t4);
    window->draw(prompt);
}

#include <cstdlib>

void Console::setOutput(sf::String s, bool speech)
{
    t1.setString(t2.getString());
    t2.setString(t3.getString());
    t3.setString(s);

    if (speech) {
        sf::String speech = "espeak.exe -v polish -s 120 --path=espeak_data \"" + s + "\"";
        std::system(speech.toAnsiString().c_str());
    }

}

void Console::setCommand(sf::String s)
{
    t4.setString(s);
}

sf::String Console::getCommand()
{
    return t4.getString();
}
