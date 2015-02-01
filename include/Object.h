#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object : public sf::Sprite
{
    public:
        Object(const sf::Texture &, std::string);
        std::string getName();
    protected:
    private:
        std::string name;
};

#endif // OBJECT_H
