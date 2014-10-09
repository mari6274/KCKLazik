#include "SFMLPhysics.h"
#include <iostream>
sf::FloatRect SFMLPhysics::getViewBounds(const sf::View &view)
{
    sf::FloatRect rt;
    rt.left = view.getCenter().x - view.getSize().x/2;
    rt.top  = view.getCenter().y - view.getSize().y/2;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;

    //std::cout << rt.left << " " << rt.top << " " << rt.width << " " << rt.height << std::endl;

    return rt;
}

sf::Vector2f SFMLPhysics::getCenterOfRect(const sf::FloatRect& rect)
{
    float x = rect.left+rect.width/2.f;
    float y = rect.top+rect.height/2.f;
    //std::cout << x << " " << y << std::endl;
    sf::Vector2f vec(x,y);
    return vec;
}

