#ifndef HELPER_H
#define HELPER_H

#include <SFML/System.hpp>
#include "Object.h"

class Helper
{
    public:
        static float distance(sf::Vector2f a, sf::Vector2f b);
        static float minimum(std::vector<Object*> & v, sf::Vector2f pozycja);
    protected:
    private:
};

#endif // HELPER_H
