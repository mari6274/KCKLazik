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

    int minimum=20000;
    for(int i=0; i<v.size(); i++)
    {
        Object * o=v.at(i);
        float dist = Helper::distance(pozycja,o->getPosition());
        if (dist < minimum)
            minimum=dist;
        //std::cout<< dist <<std::endl;
    }
    return minimum;

}

sf::FloatRect Helper::getViewBounds(const sf::View &view)
{
    sf::FloatRect rt;
    rt.left = view.getCenter().x - view.getSize().x/2;
    rt.top  = view.getCenter().y - view.getSize().y/2;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;

//    std::cout << "View bounds" << rt.left << " " << rt.top << " " << rt.width << " " << rt.height << std::endl;

    return rt;
}

sf::Vector2f Helper::getCenterOfRect(const sf::FloatRect& rect)
{
    float x = rect.left+(rect.width/2.f);
    float y = rect.top+(rect.height/2.f);
    //std::cout << x << " " << y << std::endl;
    sf::Vector2f vec(x,y);
    return vec;
}

bool Helper::containsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
//    std::cout << "rect1: " << rect1.top << " " << rect1.height << " " << rect1.left << " " << rect1.width << std::endl;
//    std::cout << "rect2: " << rect2.top << " " << rect2.height << " " << rect2.left << " " << rect2.width << std::endl << std::endl;
    if (
        rect1.top <= rect2.top &&
        rect1.left <= rect2.left &&
        (rect1.height + rect1.top) >= (rect2.height + rect2.top) &&
        (rect1.width + rect1.left) >= (rect2.width + rect2.left)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}
