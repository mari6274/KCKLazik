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

Object * Helper::minimum(std::vector<Object*> & v, sf::Vector2f pozycja)
{

    int minimum=20000;
    Object * minObj;
    for(int i=0; i<v.size(); i++)
    {
        Object * o=v.at(i);
        float dist = Helper::distance(pozycja,o->getPosition());
        if (dist < minimum)
        {
            minimum=dist;
            minObj = o;
        }
        //std::cout<< dist <<std::endl;
    }
    return minObj;

}

sf::Vector2f * Helper::minimum(std::vector<sf::Vector2f*> & v, sf::Vector2f pozycja)
{

    int minimum=20000;
    sf::Vector2f * minV2f;
    for(int i=0; i<v.size(); i++)
    {
        sf::Vector2f * v2f=v.at(i);
        float dist = Helper::distance(pozycja,*v2f);
        if (dist < minimum)
        {
            minimum=dist;
            minV2f = v2f;
        }
        //std::cout<< dist <<std::endl;
    }
    return minV2f;

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

bool Helper::checkCollisions(sf::Vector2f v, const std::vector<std::vector<Object* >* > & colliders)
{
    for (std::vector<Object*>* objs : colliders)
    {
        for (Object * o : *objs)
        {
            if (o->getGlobalBounds().contains(v)) return true;
        }
    }
    return false;
}

std::vector<Object*> Helper::getColliders(sf::Vector2f v, const std::vector<std::vector<Object* >* > & colliders)
{
    std::vector<Object*> ret;

    for (std::vector<Object*>* objs : colliders)
    {
        for (Object * o : *objs)
        {
            if (o->getGlobalBounds().contains(v)) ret.push_back(o);
        }
    }
    return ret;
}

sf::String Helper::stringZPlikuNaSfString(std::string s)
{
    std::basic_string < sf::Uint32 > tmp;
    sf::Utf8::toUtf32( s.begin(), s.end(), std::back_inserter( tmp ) );
    sf::String sfs = tmp;
    return sfs;
}

bool Helper::checkIfVectorContainsObject(Object* o, std::vector<Object *> * v)
{
    for (Object * x : *v)
    {
        if (o == x)
            return true;
    }
    return false;
}

void Helper::usunOgonki(sf::String& s)
{

    for (int i = 0; i < s.getSize() ; ++i )
    {
        usunOgonkiZnaku(&s[i]);
    }
}

void Helper::usunOgonkiZnaku(sf::Uint32 * x)
{

    if (*x == 260) *x = 65; //ą -> a
    if (*x == 261) *x = 97; //Ą -> A
    if (*x == 281) *x = 101; //ę -> e
    if (*x == 280) *x = 69; //Ę -> E
    if (*x == 243) *x = 111; //ó -> o
    if (*x == 211) *x = 79; //Ó -> O
    if (*x == 263) *x = 99; //ć -> c
    if (*x == 262) *x = 67; //Ć -> C
    if (*x == 322) *x = 108; //ł -> l
    if (*x == 321) *x = 76; //Ł -> L
    if (*x == 347) *x = 115; //ś -> s
    if (*x == 346) *x = 83; //Ś -> S
    if (*x == 378) *x = 122; //ź -> z
    if (*x == 377) *x = 90; //Ź -> Z
    if (*x == 380) *x = 122; //ż -> z
    if (*x == 379) *x = 90; //Ż -> Z
    if (*x == 324) *x = 110; //ń -> n
    if (*x == 323) *x = 78; //Ń -> N
}

std::vector<std::string> Helper::explode(const std::string& str, const char delimiter)
{
    std::vector<std::string> elements;
    std::stringstream stream(str);
    std::string item;
    while (getline(stream, item, delimiter))
        if (item!="")
            elements.push_back(item);

    return elements;
}

std::vector<std::string> Helper::dzielNaZdania(std::string in)
{
    std::string tab[] = {
        " a nastepnie ",
        "a nastepnie",
        " i ",
        " oraz ",
        " nastepnie ",
        " potem ",
        "potem",
        "nastepnie",
        "oraz"
    };

    size_t pos;

    for (std::string s : tab)
    {
        while ((pos = in.find(s)) != std::string::npos)
        {
            in.replace(pos, s.length(), "|");
        }
    }

    return Helper::explode(in, '|');
}
