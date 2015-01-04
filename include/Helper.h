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
        static Object * minimum(std::vector<Object*> & v, sf::Vector2f pozycja);
        static sf::Vector2f * minimum(std::vector<sf::Vector2f*> & v, sf::Vector2f pozycja);
        static bool checkCollisions(sf::Vector2f v, const std::vector<std::vector<Object*>*> & colliders);
        static std::vector<Object*> getColliders(sf::Vector2f v, const std::vector<std::vector<Object*>*> & colliders);
        static sf::String stringZPlikuNaSfString(std::string s);
        static bool checkIfVectorContainsObject(Object * o, std::vector<Object *> * v);

    protected:
    private:
};

#endif // HELPER_H
