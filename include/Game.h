#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Object.h"
#include <vector>
#include <AStarVector2f.h>
#include "Console.h"
#include "InfoBox.h"

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
        InfoBox * infoBox;

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



#endif // GAME_H
