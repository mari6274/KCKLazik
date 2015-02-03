#include "Game.h"
#include "TaskManager.h"
#include "Helper.h"

#include <iostream>

Game::Game()
{
    taskManager = new TaskManager(this);
    console = new Console(&window);
    command = "";
    infoBox = new InfoBox(&window);
}

void Game::start()
{
    loadTextures();
    tMap.setRepeated(true);
    sMap.setTexture(tMap);
    sMap.setTextureRect(sf::IntRect(0,0,3000,2000));

    window.create(sf::VideoMode(WINDOWX+200, WINDOWY), L"Łazik Marsjański");

    rover.setTexture(tRover);
    rover.setOrigin(rover.getGlobalBounds().width/2, rover.getGlobalBounds().height/2);
    rover.setPosition(1525,1025);


    view.setSize(WINDOWX, WINDOWY-150);
    view.setCenter(rover.getPosition());
    view.setViewport(sf::FloatRect(0, 0, 0.8f, 0.75f));
    window.setView(view);

    miniMap.setSize(200,150);
    miniMap.setCenter(view.getCenter());
    miniMap.setViewport(sf::FloatRect(0.8f, 0.75f, 0.2f, 0.25f));
    miniMap.zoom(16.0f);
    window.setView(miniMap);

    window.setFramerateLimit(60);

    srand(time(NULL));
    generateRandPosObjects(crater, 6, craters, "krater");
    generateRandPosObjects(rock1, 20, rocks, "skała");
    generateRandPosObjects(rock2, 20, rocks, "skała");

    //vector of colliders
    colliders.push_back(&rocks);
    colliders.push_back(&craters);
    //vector of noncolliders

    while (window.isOpen())
    {
        enter = false;

        window.clear();

        while (window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                exit(0);
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                enter = true;
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                command = console->getAndSetLastCommand();
            }

            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == 8)
                {
                    if (command.getSize() > 0) command.erase(command.getSize() -1, command.getSize());
                }
                else if (event.text.unicode != 13 && command.getSize() < 90)
                {
                    command=command+event.text.unicode;
                }
                console->setCommand(command);
            }

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

        window.setView(window.getDefaultView());
        //
        console->draw();
        infoBox->draw();
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

void Game::generateRandPosObjects(sf::Texture & texture, int n, std::vector<Object*> & v, std::string name)
{
    for (int i = 0; i<n; ++i)
    {
        Object * o = new Object(texture, name);
        int width = (int)(o->getGlobalBounds().width/50);
        int height = (int)(o->getGlobalBounds().height/50);
        do
        {
            o->setPosition((rand()%(60-width))*50, (rand()%(40-height))*50);
        } while (Helper::checkCollisions(o->getPosition(), colliders) || o->getGlobalBounds().intersects(rover.getGlobalBounds()));

        int orx = o->getGlobalBounds().width/2;
        orx = orx/50;
        orx = orx * 50;
        int ory = o->getGlobalBounds().height/2;
        ory = ory/50;
        ory = ory * 50;
        o->setOrigin(orx, ory);
        o->move(orx, ory);
        v.push_back(o);
    }
}

TaskManager * Game::getTaskManager()
{
    return taskManager;
}

