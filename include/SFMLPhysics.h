#ifndef SFMLPHYSICS_H
#define SFMLPHYSICS_H

#include <SFML/Graphics.hpp>

class SFMLPhysics
{
    public:
        static sf::FloatRect getViewBounds(const sf::View &view);
        static sf::Vector2f getCenterOfRect(const sf::FloatRect &rect);
    protected:
    private:
};

#endif // SFMLPHYSICS_H
