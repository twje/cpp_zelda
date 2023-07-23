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
    sf::Clock mClock;
    Level mLevel;
    LevelView mLevelView;
};