#include "Game.h"
#include "Helper.h"

#include <iostream>

Game::Game()
{
    taskManager = new TaskManager(this);
}

void Game::start()
{
    loadTextures();
    tMap.setRepeated(true);
    sMap.setTexture(tMap);
    sMap.setTextureRect(sf::IntRect(0,0,3000,2000));

    window.create(sf::VideoMode(WINDOWX+200, WINDOWY), "sfmlview");

    rover.setTexture(tRover);
    rover.setPosition(1525,1025);
    rover.setOrigin(rover.getGlobalBounds().width/2, rover.getGlobalBounds().height/2);

    view.setSize(WINDOWX, WINDOWY);
    view.setCenter(rover.getPosition());
    view.setViewport(sf::FloatRect(0, 0, 0.8f, 1));
    window.setView(view);

    miniMap.setSize(200,150);
    miniMap.setCenter(view.getCenter());
    miniMap.setViewport(sf::FloatRect(0.8f, 0.75f, 0.2f, 0.25f));
    miniMap.zoom(16.0f);
    window.setView(miniMap);

    window.setFramerateLimit(60);

    srand(time(NULL));
    generateRandPosObjects(crater, 3, craters, "Krater");
//    for (Object * o : craters)
//    {
//        o->setScale((rand()%10+5)/10.f, (rand()%10+5)/10.f);
//        o->setRotation(rand()%360);
//    }
    generateRandPosObjects(rock1, 5, rocks, "Skała");
    generateRandPosObjects(rock2, 5, rocks, "Skała");

    //vector of colliders
    colliders.push_back(&rocks);
    //vector of noncolliders
    noncolliders.push_back(&craters);

    while (window.isOpen())
    {
        window.clear();

        while (window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                exit(0);
            }

//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) taskManager->move(-100, 0);
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) taskManager->move(100, 0);
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) taskManager->move(0, -100);
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) taskManager->move(0, 100);
        }

        window.setView(view);
        window.draw(sMap);
        for (std::vector<Object*> * vec : noncolliders)
        {
            for (Object * t : *vec)
            {
                window.draw(*t);
            }
        }
        for (std::vector<Object*> * vec : colliders)
        {
            for (Object * t : *vec)
            {
                window.draw(*t);
            }
        }

        window.draw(miniMapRect);

        window.draw(rover);

        window.setView(miniMap);
        window.draw(sMap);
        for (std::vector<Object*> * vec : noncolliders)
        {
            for (Object * t : *vec)
            {
                window.draw(*t);
            }
        }
        for (std::vector<Object*> * vec : colliders)
        {
            for (Object * t : *vec)
            {
                window.draw(*t);
            }
        }


        window.draw(rover);

        window.display();
    }

}

void Game::loadTextures()
{
    if (!tMap.loadFromFile("img/mars.jpg"))
    {
        exit(0);
    }
    if (!tRover.loadFromFile("img/rover.png"))
    {
        exit(0);
    }
    if (!crater.loadFromFile("img/crater.png"))
    {
        exit(0);
    }
    if (!rock1.loadFromFile("img/rock1.png"))
    {
        exit(0);
    }
    if (!rock2.loadFromFile("img/rock2.png"))
    {
        exit(0);
    }
}

void Game::generateRandPosObjects(sf::Texture & texture, int n, std::vector<Object*> & v, sf::String name)
{
    for (int i = 0; i<n; ++i)
    {
        Object * o = new Object(texture, name);
        int width = (int)(o->getGlobalBounds().width/50);
        int height = (int)(o->getGlobalBounds().height/50);
        o->setPosition(((rand()%(60-width))+width/2)*50, ((rand()%(40-height))+height/2)*50);
        //o->setOrigin(o->getGlobalBounds().width/2, o->getGlobalBounds().height/2);

        v.push_back(o);
    }
}

TaskManager * Game::getTaskManager()
{
    return taskManager;
}

TaskManager::TaskManager(Game * game)
{
    this->game = game;
}

bool TaskManager::move(int x, int y)
{
    sf::Vector2f v = game->rover.getPosition();
    v.y += y*50;
    v.x += x*50;

    if (goTo(v)) return true;
        else return false;
}

bool TaskManager::goCoordinates(int x, int y, bool automatic) {
    sf::Vector2f v;
    v.x = (x%50)+25;
    v.y = (y%50)+25;
    if (automatic)
    {
        goToAuto(v);
    }
    else
    {
        if (goTo(v)) return true;
            else return false;
    }

}

sf::Vector2f TaskManager::getCoordinates() {
    return game->rover.getPosition();
}

bool TaskManager::goTo(sf::Vector2f v)
{
    if (!game->sMap.getGlobalBounds().contains(v)) {
        error = "Podana pozycja jest poza obszarem eksploracji";
        return false;
    }


    sf::Sprite rov = game->rover;

    while (v != rov.getPosition())
    {
        sf::sleep(sf::milliseconds(50));
        rov = game->rover;

        sf::Vector2f p1 = rov.getPosition();
        p1.x -= 50;
        sf::Vector2f p2 = rov.getPosition();
        p2.x += 50;
        sf::Vector2f p3 = rov.getPosition();
        p3.y -= 50;
        sf::Vector2f p4 = rov.getPosition();
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

        rov.setPosition(*Helper::minimum(p, v));

        for (std::vector<Object*> * vect : game->colliders)
        {
            for (Object * o : *vect)
            {
                if (rov.getGlobalBounds().intersects(o->getGlobalBounds()))
                {
                    error =  "Nie można przejść gdyż napotkano obiekt: " + o->getName().toAnsiString();
                    return false;
                }
            }
        }

        game->rover.setPosition(rov.getPosition());
        if (!Helper::containsRect(Helper::getViewBounds(game->view), game->rover.getGlobalBounds())) game->view.setCenter(game->rover.getPosition());
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

bool TaskManager::rotate(int angle)
{
    sf::Sprite rov = game->rover;

    rov.setRotation(angle);

    for (std::vector<Object*> * vect : game->colliders)
    {
        for (Object * o : *vect)
        {
            if (rov.getGlobalBounds().intersects(o->getGlobalBounds()))
            {
                error =  "Nie można się obrócić gdyż napotkano obiekt: " + o->getName().toAnsiString();
                return false;
            }
        }
    }

    game->rover.setRotation(rov.getRotation());

    return true;
}

Object * TaskManager::getLocalObject()
{
    for (std::vector<Object*> * vect : game->colliders)
    {
        for (Object * o : *vect)
        {
            if (game->rover.getGlobalBounds().intersects(o->getGlobalBounds())) return o;
        }
    }

    return NULL;
}

bool TaskManager::goToAuto(sf::Vector2f v)
{
    std::vector<AStarVector2f*> path = AStar(v);
    for (auto it = path.end()-2; it!=path.begin()-1; --it)
    {
        sf::sleep(sf::milliseconds(500));
        game->rover.setPosition(*(*it));
        game->view.setCenter(*(*it));
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
    sf::Vector2f start = game->rover.getPosition();
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

    sf::Vector2f rov = game->rover.getPosition();

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

        //sąsiedzi
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
}
