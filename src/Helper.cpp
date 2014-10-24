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

//float Helper::minimum(std::vector<Object*> & v, sf::Vector2f pozycja)
//{
//// to nie dziala ale nie wiem czemu
////vektor drzew wlozony
//
//    int minimum=2000;
//    for(int i=0; i<v.size(); i++)
//    {
//        o=v.at(i);
//
//        if (Helper::distance(pozycja,o->getPosition())<minimum)
//            minimum=Helper::distance(pozycja,o->getPosition());
//        std::cout<<Helper::distance(pozycja,o->getPosition())<<std::endl;
//
//
//    }
//
//    return minimum;
//
//}
