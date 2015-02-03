#include "TaskManager.h"
#include <sstream>

TaskManager::TaskManager(Game * game)
{
    this->game = game;
}

bool TaskManager::move(int x, int y)
{
    sf::Vector2f v = getRoverPosition();
    v.y += y*50;
    v.x += x*50;

    if (goTo(v)) return true;
        else return false;
}

bool TaskManager::goCoordinates(int x, int y, bool automatic) {
    sf::Vector2f v;
    v.x = x*50;
    v.y = y*50;
    if (automatic)
    {
        return goToAuto(v);
    }
    else
    {
        return goTo(v);
    }

}

sf::Vector2f TaskManager::getCoordinates() {
    return getRoverPosition();
}

bool TaskManager::goTo(sf::Vector2f v)
{
    sf::Vector2f rov = getRoverPosition();

    while (v != rov)
    {
        sf::sleep(sf::milliseconds(150));
        rov = getRoverPosition();

        sf::Vector2f p1 = rov;
        p1.x -= 50;
        sf::Vector2f p2 = rov;
        p2.x += 50;
        sf::Vector2f p3 = rov;
        p3.y -= 50;
        sf::Vector2f p4 = rov;
        p4.y += 50;
        sf::Vector2f p13(p1.x, p3.y);
        sf::Vector2f p14(p1.x, p4.y);
        sf::Vector2f p23(p2.x, p3.y);
        sf::Vector2f p24(p2.x, p4.y);

        std::vector<sf::Vector2f *> p;
        p.push_back(&p1);
        p.push_back(&p2);
        p.push_back(&p3);
        p.push_back(&p4);
        p.push_back(&p13);
        p.push_back(&p14);
        p.push_back(&p23);
        p.push_back(&p24);

        rov = *Helper::minimum(p, v);

        for (std::vector<Object*> * vect : game->colliders)
        {
            for (Object * o : *vect)
            {
                if (o->getGlobalBounds().contains(rov))
                {
                    error =  "Nie można przejść gdyż napotkano obiekt: " + o->getName();
                    return false;
                }
            }
        }

        if (!game->sMap.getGlobalBounds().contains(rov)) {
            error = "Podana pozycja jest poza obszarem eksploracji";
            return false;
        }

        setRoverPosition(rov);
        game->view.setCenter(game->rover.getPosition());
    }

    return true;
}

void TaskManager::quit() {
    game->window.close();
    exit(0);
}

sf::String TaskManager::getError() {
    return error;
}

void TaskManager::rotate(int angle)
{
    game->rover.setRotation(angle);
}

std::vector<Object *> TaskManager::getLocalObjects(int distance, bool print)
{
    std::vector<Object *> localObjects;
    for (int i = -distance; i<=distance; ++i)
    {
        for (int j = -distance; j<=distance; ++j)
        {
            float x = getRoverPosition().x + i*50;
            float y = getRoverPosition().y + j*50;
            sf::Vector2f v(x,y);
            std::vector<Object*> temp = Helper::getColliders(v, game->colliders);
            for (Object* o : temp)
            {
                if (!Helper::checkIfVectorContainsObject(o, &localObjects))
                    localObjects.push_back(o);
            }
        }
    }

    std::string s;
    for (int i = 0 ; i < localObjects.size(); ++i)
    {
        std::stringstream ss;
        ss << localObjects[i]->getPosition().x << " " << localObjects[i]->getPosition().y << " " << i+1;
        std::string stds1;
        std::string stds2;
        std::string stdsi;
        ss >> stds1 >> stds2 >> stdsi;

        s += stdsi + ". " + localObjects[i]->getName() + " (" + stds1 + ", " + stds2 + ")\n";
    }

    if (print) setInfo(s);

    return localObjects;
}

std::vector<Object*> TaskManager::getNeighbors(bool print)
{

    return getLocalObjects(1, print);

}

bool TaskManager::goToAuto(sf::Vector2f v)
{
    if (!game->sMap.getGlobalBounds().contains(v)) {
        error = "Podana pozycja jest poza obszarem eksploracji";
        return false;
    }

    for (std::vector<Object*>* objs : game->colliders)
    {
        for (Object * o : *objs)
        {
            if (o->getGlobalBounds().contains(v)) {
                error = "Pozycja koliduje z obiektem: " + o->getName();
                return false;
            }
        }
    }

    std::vector<AStarVector2f*> path = AStar(v);
    if (!path.empty())
    {
        for (auto it = path.end()-2; it!=path.begin()-1; --it)
        {
            sf::sleep(sf::milliseconds(150));
            setRoverPosition(*(*it));
            game->view.setCenter(game->rover.getPosition());
        }
        for (AStarVector2f * a : path)
        {
            delete a;
        }
        return true;
    }
    else {
        error = "Nie można znaleźć trasy.";
        return false;
    }
}

float TaskManager::calcF(AStarVector2f * a, sf::Vector2f target)
{
    return a->g+Helper::distance(*a, target);
}

std::vector<AStarVector2f*> TaskManager::generatePath(AStarVector2f* a)
{
    AStarVector2f debug = *a;
    std::vector<AStarVector2f*> path;
    sf::Vector2f start = getRoverPosition();
    while (start != *(a->parent))
    {
        debug = *a;
        path.push_back(a);
        a = a->parent;
    }
    return path;
}

bool TaskManager::checkCollisions(sf::Vector2f v)
{
    if (v.x < 0 || v.x > 59*50 || v.y < 0 || v.y > 39*50) return true;

    for (std::vector<Object*>* objs : game->colliders)
    {
        for (Object * o : *objs)
        {
            if (o->getGlobalBounds().contains(v)) return true;
        }
    }
    return false;
}

std::vector<AStarVector2f*> TaskManager::AStar(sf::Vector2f target)
{
    std::vector<AStarVector2f*> CL;
    std::vector<AStarVector2f*> OL;

    sf::Vector2f rov = getRoverPosition();

    AStarVector2f * start = new AStarVector2f(rov.x, rov.y);
    start->parent = start;
    OL.push_back(start);

    while (!OL.empty())
    {

        AStarVector2f * q = OL.front();
        auto qit = OL.begin();
        for (auto it = OL.begin(); it != OL.end(); ++it)
        {
            if (calcF(*it, target) < calcF(q, target))
            {
                q = *it;
                qit = it;
            }
        }
        CL.push_back(q);
        OL.erase(qit);

        if (*q == target)
        {

            std::vector<AStarVector2f*> path= generatePath(q);
            return path;
        }

        //sĂ„â€¦siedzi
        AStarVector2f * u = new AStarVector2f(q->x, q->y-50);
        AStarVector2f * r = new AStarVector2f(q->x+50, q->y);
        AStarVector2f * d = new AStarVector2f(q->x, q->y+50);
        AStarVector2f * l = new AStarVector2f(q->x-50, q->y);
        AStarVector2f * ur = new AStarVector2f(q->x+50, q->y-50);
        AStarVector2f * dr = new AStarVector2f(q->x+50, q->y+50);
        AStarVector2f * dl = new AStarVector2f(q->x-50, q->y+50);
        AStarVector2f * ul = new AStarVector2f(q->x-50, q->y-50);

        std::vector<AStarVector2f*> neights;
        neights.push_back(u);
        neights.push_back(r);
        neights.push_back(d);
        neights.push_back(l);
        neights.push_back(ur);
        neights.push_back(dr);
        neights.push_back(dl);
        neights.push_back(ul);

        for (AStarVector2f * a : neights)
        {
            bool onCL = false;
            for (AStarVector2f * b : CL)
            {
                if (*b == *a) {
                    onCL = true;
                    break;
                }
            }

            bool onOL = false;
            auto itOl = OL.begin();
            for (auto it = OL.begin(); it != OL.end(); ++it)
            {
                if ((*(*it)) == *a) {
                    onOL = true;
                    itOl = it;
                    break;
                }
            }

            if (checkCollisions(*a) || onCL) {}
            else if (!onOL)
            {
                a->parent = q;
                a->g = Helper::distance(*a, *q)+q->g;
                OL.push_back(a);
            }
            else
            {
                float nowaG = Helper::distance(*a, *q)+q->g;
                if (nowaG < (*itOl)->g)
                {
                    (*itOl)->parent = q;
                    (*itOl)->g = nowaG;
                }
                delete a;
            }
        }
        std::cout << q->x << " " << q->y << "\t" << q->parent->x << " " << q->parent->y << std::endl;
    }
    std::vector<AStarVector2f*> path;
    return path;
}

Console * Game::getConsole()
{
    return console;
}

sf::String TaskManager::readCommand(bool ogonki)
{

    sf::Event event;
    while (!game->enter || game->command=="")
    {

    }
    game->enter = false;
    sf::String temp = game->command;
    game->console->setOutputFromKeyboard(temp, false);
    if (!ogonki) Helper::usunOgonki(temp);
    game->console->setCommand("");

    game->command = "";

    std::string out;
    sf::Utf32::toUtf8(temp.begin(), temp.end(), std::back_inserter(out));
    return out;
}

void TaskManager::setInfo(std::string info)
{
    game->infoBox->setInfo(Helper::stringZPlikuNaSfString(info));
}

sf::Vector2f TaskManager::getRoverPosition()
{
    sf::Vector2f v(game->rover.getPosition().x-25, game->rover.getPosition().y-25);
    return v;
}

void TaskManager::setRoverPosition(float x, float y)
{
    game->rover.setPosition(x+25, y+25);
}

void TaskManager::setRoverPosition(sf::Vector2f v)
{
    game->rover.setPosition(v.x+25, v.y+25);
}
