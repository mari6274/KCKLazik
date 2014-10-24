#include "Helper.h"
#include <iostream>
#include <math.h>


float Helper::distance(sf::Vector2f a, sf::Vector2f b)
{
    float width = abs(a.x-b.x);
    float height = abs(a.y-b.y);
    float distance = sqrt(pow(width, 2)+pow(height,2));
    return distance;
}

float Helper::minimum(std::vector<Object*> & v, sf::Vector2f pozycja)
{
// to nie dziala ale nie wiem czemu
//vektor drzew wlozony

    int minimum=20000;
    for(int i=0; i<v.size(); i++)
    {
        Object * o=v.at(i);
        float dist = Helper::distance(pozycja,o->getPosition());
        if (dist < minimum)
            minimum=dist;
        std::cout<< dist <<std::endl;
    }
    return minimum;

}
