#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object : public sf::Sprite
{
    public:
        Object(const sf::Texture &, sf::String);
        sf::String getName();
    protected:
    private:
        sf::String name;
};

#endif // OBJECT_H
