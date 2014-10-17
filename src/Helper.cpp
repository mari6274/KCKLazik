#include "Helper.h"

#include <math.h>

float Helper::distance(sf::Vector2f a, sf::Vector2f b) {
    float width = abs(a.x-b.x);
    float height = abs(a.y-b.y);
    float distance = sqrt(pow(width, 2)+pow(height,2));
    return distance;
}
