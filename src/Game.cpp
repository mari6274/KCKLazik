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
    rover.setOrigin(rover.getGlobalBounds().width/2, rover.getGlobalBounds().height/2);
    rover.setPosition(1500,1000);

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
    generateRandPosObjects(crater, 3, craters);
    for (Object * o : craters)
    {
        o->setScale((rand()%10+5)/10.f, (rand()%10+5)/10.f);
//        o->setRotation(rand()%360);
    }

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

            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) taskManager->move(-100, 0);
            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) taskManager->move(100, 0);
            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) taskManager->move(0, -100);
            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) taskManager->move(0, 100);
        }

        window.setView(view);
        window.draw(sMap);
        for (Object * t : craters)
        {
            window.draw(*t);
        }

        window.draw(miniMapRect);

        window.draw(rover);

        window.setView(miniMap);
        window.draw(sMap);
        for (Object * t : craters)
        {
            window.draw(*t);
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
}

void Game::generateRandPosObjects(sf::Texture & texture, int n, std::vector<Object*> & v)
{
    for (int i = 0; i<n; ++i)
    {
        Object * o = new Object(texture, "krater");
        o->setOrigin(o->getGlobalBounds().width/2, o->getGlobalBounds().height/2);
        o->setPosition(rand()%3000, rand()%2000);
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
    v.y += y;
    v.x += x;

    if (goTo(v)) return true;
        else return false;
}

bool TaskManager::goCoordinates(int x, int y) {
    sf::Vector2f v;
    v.x = x;
    v.y = y;
    if (goTo(v)) return true;
        else return false;
}

sf::Vector2f TaskManager::getCoordinates() {
    return game->rover.getPosition();
}

bool TaskManager::goTo(sf::Vector2f v)
{
    sf::Sprite rov = game->rover;

    while (v != rov.getPosition())
    {
        sf::sleep(sf::milliseconds(5));
        rov = game->rover;

        sf::Vector2f p1 = rov.getPosition();
        p1.x -= 1;
        sf::Vector2f p2 = rov.getPosition();
        p2.x += 1;
        sf::Vector2f p3 = rov.getPosition();
        p3.y -= 1;
        sf::Vector2f p4 = rov.getPosition();
        p4.y += 1;

        float distp1 = Helper::distance(v, p1);
        float distp2 = Helper::distance(v, p2);
        float distp3 = Helper::distance(v, p3);
        float distp4 = Helper::distance(v, p4);

        if (distp1 <= distp2 && distp1 <= distp3 && distp1 <= distp4) { rov.setPosition(p1); }
            else if (distp2 <= distp1 && distp2 <= distp3 && distp2 <= distp4) rov.setPosition(p2);
                else if (distp3 <= distp1 && distp3 <= distp2 && distp3 <= distp4) rov.setPosition(p3);
                    else rov.setPosition(p4);


        for (Object * o : game->craters)
        {
            if (rov.getGlobalBounds().intersects(o->getGlobalBounds()))
            {
                error =  "Nie można przejść gdyż napotkano obiekt: " + o->getName().toAnsiString();
                return false;
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
