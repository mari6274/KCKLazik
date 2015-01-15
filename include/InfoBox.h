#ifndef INFOBOX_H
#define INFOBOX_H

#include <SFML/Graphics.hpp>

class InfoBox
{
    public:
        InfoBox(sf::RenderWindow * window);
        void draw();
        void setInfo(sf::String info);
    protected:
    private:
        sf::RenderWindow * window;
        sf::Font arial;
        sf::Text infoHeader;
        sf::Text infoText;
        sf::String wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold = false);
};

#endif // INFOBOX_H
