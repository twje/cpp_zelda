#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"

class Game
{
public:
    Game();
    void Run();

private:
    sf::RenderWindow mWindow;
    Level mLevel;
};