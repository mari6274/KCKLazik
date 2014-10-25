#ifndef HELPER_H
#define HELPER_H

#include <SFML/Graphics.hpp>
#include "Object.h"

class Helper
{
    public:
        static sf::FloatRect getViewBounds(const sf::View &view);
        static sf::Vector2f getCenterOfRect(const sf::FloatRect &rect);
        static bool containsRect(const sf::FloatRect &rect1, const sf::FloatRect &rect2);
        static float distance(sf::Vector2f a, sf::Vector2f b);
        static float minimum(std::vector<Object*> & v, sf::Vector2f pozycja);
    protected:
    private:
};

#endif // HELPER_H
