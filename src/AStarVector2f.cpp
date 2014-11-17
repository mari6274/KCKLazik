#include "AStarVector2f.h"

AStarVector2f::AStarVector2f(float x, float y) : sf::Vector2f(x, y)
{
    parent = NULL;
    g = NULL;
}
