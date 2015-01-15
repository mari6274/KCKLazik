#include "InfoBox.h"

InfoBox::InfoBox(sf::RenderWindow * window)
{
    this->window = window;

    if (!arial.loadFromFile("arial.ttf"))
    {
        exit(0);
    }

    infoHeader.setCharacterSize(14);
    infoHeader.setFont(arial);
    infoHeader.setPosition(810, 20);
    infoHeader.setString("Info BoX");

    infoText.setCharacterSize(12);
    infoText.setFont(arial);
    infoText.setPosition(810, 40);
}

void InfoBox::draw()
{
    window->draw(infoText);
    window->draw(infoHeader);
}

void InfoBox::setInfo(sf::String info)
{
    infoText.setString(wrapText(info, 180, arial, 14));
}

sf::String InfoBox::wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold){
    unsigned currentOffset = 0;
    bool firstWord = true;
    std::size_t wordBegining = 0;

    for (std::size_t pos(0); pos < string.getSize(); ++pos) {
        auto currentChar = string[pos];
        if (currentChar == '\n'){
            currentOffset = 0;
            firstWord = true;
            continue;
        } else if (currentChar == ' ') {
            wordBegining = pos;
            firstWord = false;
        }

        auto glyph = font.getGlyph(currentChar, charicterSize, bold);
        currentOffset += glyph.advance;

        if (!firstWord && currentOffset > width) {
            pos = wordBegining;
            string[pos] = '\n';
            firstWord = true;
            currentOffset = 0;
        }
    }

    return string;
}
