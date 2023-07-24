#pragma once

#include <SFML/Graphics.hpp>

// Game
#include "Level.h"
#include "LevelView.h"

class Game
{
public:
    Game();
    void Run();

private:
    sf::RenderWindow mWindow;
    Level mLevel;
    LevelView mLevelView;
    sf::Clock mClock;
};