#include "Object.h"

Object::Object(const sf::Texture & texture, sf::String name) : sf::Sprite(texture)
{
    this->name = name;
}

sf::String Object::getName()
{
    return this->name;
}
