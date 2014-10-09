#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class TaskManager;

class Game
{
    friend class TaskManager;
    public:
        Game();
        void start();
        TaskManager * getTaskManager();
    protected:
    private:
        TaskManager * taskManager;

        const int WINDOWX = 800;
        const int WINDOWY = 600;

        sf::RenderWindow window;
        sf::Texture tMap;
        sf::Sprite sMap;
        sf::RectangleShape miniMapRect;
        sf::View view;
        sf::View miniMap;

        sf::Sprite cookie;

        sf::Event event;
        int speed = 48;

        void createMiniMapRect();
};

class TaskManager {
    public:
        TaskManager(Game * game);
        void goLeft();
        void goRight();
        void goUp();
        void goDown();
    private:
        Game * game;
};

#endif // GAME_H
