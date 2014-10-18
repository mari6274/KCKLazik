#include "Game.h"
#include "SFMLPhysics.h"

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

    //createMiniMapRect();

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

    cookie.setTexture(tCookie);
    cookie.setOrigin(cookie.getGlobalBounds().width/2, cookie.getGlobalBounds().height/2);
    cookie.setPosition(view.getCenter());

    srand(time(NULL));
    generateRandPosObjects(tree, 20, trees);
    generateRandPosObjects(cave, 8, caves);

    while (window.isOpen()) {
        window.clear();

        while (window.pollEvent(event)) {

            if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
                exit(0);
            }
//            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//                view.setCenter(view.getCenter().x+sf::Mouse::getPosition(window).x-400, view.getCenter().y+sf::Mouse::getPosition(window).y-300) ;
//            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) taskManager->goLeft();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) taskManager->goRight();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) taskManager->goUp();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) taskManager->goDown();
        }

        window.setView(view);
        window.draw(sMap);
        for (Object * t : caves) { window.draw(*t); }
        for (Object * t : trees) { window.draw(*t); }
        //miniMapRect.setPosition(view.getCenter().x+window.getSize().x/5, view.getCenter().y+window.getSize().y/4);
        window.draw(miniMapRect);

        window.draw(cookie);

        window.setView(miniMap);
        window.draw(sMap);
        for (Object * t : caves) { window.draw(*t); }
        for (Object * t : trees) { window.draw(*t); }
        window.draw(cookie);

        window.display();
    }

}

void Game::loadTextures() {
    if (!tMap.loadFromFile("img/grass.png")) { exit(0); }
    if (!tCookie.loadFromFile("img/cookie.png")) { exit(0); }
    if (!tree.loadFromFile("img/tree.png")) { exit(0); }
    if (!cave.loadFromFile("img/cave.png")) { exit(0); }
}

void Game::createMiniMapRect() {
    miniMapRect.setSize(sf::Vector2f(202,152));
    miniMapRect.setFillColor(sf::Color::Black);
    miniMapRect.setOutlineThickness(2);
    miniMapRect.setOutlineColor(sf::Color::Red);
}
#include <random>
void Game::generateRandPosObjects(sf::Texture & texture, int n, std::vector<Object*> & v) {
    for (int i = 0; i<n; ++i) {
        Object * o = new Object(texture);
        o->setOrigin(o->getGlobalBounds().width/2, o->getGlobalBounds().height/2);
        o->setPosition(rand()%3000, rand()%2000);
        v.push_back(o);
    }
}

TaskManager * Game::getTaskManager() {
    return taskManager;
}

TaskManager::TaskManager(Game * game) {
    this->game = game;
}

void TaskManager::goLeft() {
    game->cookie.move(-game->speed, 0);
    if (!SFMLPhysics::getViewBounds(game->view).contains(SFMLPhysics::getCenterOfRect(game->cookie.getGlobalBounds()))) game->view.move(-game->speed, 0);
}

void TaskManager::goRight() {
    game->cookie.move(game->speed, 0);
    if (!SFMLPhysics::getViewBounds(game->view).contains(SFMLPhysics::getCenterOfRect(game->cookie.getGlobalBounds()))) game->view.move(game->speed, 0);
}

void TaskManager::goUp() {
    game->cookie.move(0, -game->speed);
    if (!SFMLPhysics::getViewBounds(game->view).contains(SFMLPhysics::getCenterOfRect(game->cookie.getGlobalBounds()))) game->view.move(0, -game->speed);
}

void TaskManager::goDown() {
    game->cookie.move(0, game->speed);
    if (!SFMLPhysics::getViewBounds(game->view).contains(SFMLPhysics::getCenterOfRect(game->cookie.getGlobalBounds()))) game->view.move(0, game->speed);
}
