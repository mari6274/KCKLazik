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

    view.setSize(WINDOWX, WINDOWY);
    view.setCenter(1500,1000);
    view.setViewport(sf::FloatRect(0, 0, 0.8f, 1));
    window.setView(view);

    miniMap.setSize(200,150);
    miniMap.setCenter(view.getCenter());
    miniMap.setViewport(sf::FloatRect(0.8f, 0.75f, 0.2f, 0.25f));
    miniMap.zoom(16.0f);
    window.setView(miniMap);

    window.setFramerateLimit(60);

    rover.setTexture(tRover);
    rover.setOrigin(Helper::getCenterOfRect(rover.getGlobalBounds()));
    rover.setPosition(view.getCenter());

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) taskManager->move(-10, 0);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) taskManager->move(10, 0);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) taskManager->move(0, -10);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) taskManager->move(0, 10);
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
        o->setOrigin(Helper::getCenterOfRect(o->getLocalBounds()));
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
    sf::FloatRect fr = game->rover.getGlobalBounds();
    fr.top += y;
    fr.left += x;
    for (Object * o : game->craters)
    {
        if (fr.intersects(o->getGlobalBounds()))
        {
            std::wcout << L"Nie można przejść gdyż napotkano obiekt: " << o->getName().toWideString() << std::endl;
            return false;
        }
    }

    game->rover.move(x, y);
    if (!Helper::containsRect(Helper::getViewBounds(game->view), game->rover.getGlobalBounds())) game->view.setCenter(game->rover.getPosition());
    return true;
}

bool TaskManager::goCoordinates(int x, int y) {
    game->rover.setPosition(x,y);
    return true;
}

sf::Vector2f TaskManager::getCoordinates() {
    return game->rover.getPosition();
}
