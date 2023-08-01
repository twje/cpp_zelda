#pragma once

#include <SFML/Graphics.hpp>

// Game
#include "Level.h"
#include "LevelView.h"
#include "UI.h"

class Game
{
public:
    Game();
    void Run();

private:
    sf::Clock mClock;
    sf::RenderWindow mWindow;
    UI mUI;
    Level mLevel;
    LevelView mLevelView;
};