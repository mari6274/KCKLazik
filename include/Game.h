#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Object.h"
#include <vector>
#include <AStarVector2f.h>
#include "Console.h"

class TaskManager;

class Game
{
    friend class TaskManager;
    public:
        Game();
        void start();
        TaskManager * getTaskManager();
        Console * getConsole();
    protected:
    private:
        TaskManager * taskManager;

        const int WINDOWX = 800;
        const int WINDOWY = 600;

        //textures
        sf::Texture tMap;
        sf::Texture crater;
        sf::Texture rock1;
        sf::Texture rock2;
        sf::Texture tRover;

        sf::RenderWindow window;
        sf::Sprite sMap;
        sf::RectangleShape miniMapRect;
        sf::View view;
        sf::View miniMap;
        Console * console;

        std::vector<std::vector<Object*>*> colliders;
        std::vector<std::vector<Object*>*> noncolliders;
        sf::Sprite rover;
        std::vector<Object*> craters;
        std::vector<Object*> rocks;

        sf::Event event;

        void loadTextures();
        void generateRandPosObjects(sf::Texture &, int, std::vector<Object*> &, sf::String);

        sf::String command;
        bool enter;
};

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
        bool goTo(sf::Vector2f v);
        bool goToAuto(sf::Vector2f v);
        float calcF(AStarVector2f * a, sf::Vector2f target);
        std::vector<AStarVector2f*> generatePath(AStarVector2f * a);
        bool checkCollisions(sf::Vector2f v);
        std::vector<AStarVector2f*> AStar(sf::Vector2f target);
        sf::String error;
};

#endif // GAME_H
