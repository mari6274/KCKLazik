#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Helper.h"

class Game;

class TaskManager {
    public:
        TaskManager(Game * game);

        void quit();
        bool move(int x, int y);
        void rotate(int angle);
        bool goCoordinates(int x, int y, bool automatic = false);

        sf::Vector2f getCoordinates();
        std::vector<Object*> getLocalObjects(int distance);
        std::vector<Object*> getNeighbors();
        sf::String getError();

        sf::String readCommand();
    private:
        Game * game;
        sf::String error;

        bool goTo(sf::Vector2f v);
        bool goToAuto(sf::Vector2f v);
        float calcF(AStarVector2f * a, sf::Vector2f target);
        std::vector<AStarVector2f*> generatePath(AStarVector2f * a);
        bool checkCollisions(sf::Vector2f v);
        std::vector<AStarVector2f*> AStar(sf::Vector2f target);

};

#endif // TASKMANAGER_H