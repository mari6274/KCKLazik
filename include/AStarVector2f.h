#ifndef ASTARVECTOR2F_H
#define ASTARVECTOR2F_H

#include <SFML/System.hpp>

class AStarVector2f : public sf::Vector2f
{
    public:
        AStarVector2f(float x, float y);
        float g;
        AStarVector2f * parent;

    protected:
    private:
};

#endif // ASTARVECTOR2F_H
