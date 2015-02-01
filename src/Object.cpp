#include "Object.h"

Object::Object(const sf::Texture & texture, std::string name) : sf::Sprite(texture)
{
    this->name = name;
}

std::string Object::getName()
{
    return this->name;
}
