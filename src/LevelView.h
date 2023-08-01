#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Core/SpriteGroup.h"

// Forward declarations
class Level;
class Sprite;
class UI;

class LevelView
{
public:
    LevelView(sf::RenderWindow &window, const Level &level, const UI &ui);

    void Draw(sf::RenderWindow &window);

private:
    void DebugWorldDraw(sf::RenderWindow &window);
    void DebugDrawPlayer(sf::RenderWindow &window);
    void DebugHitbox(sf::RenderWindow &window);
    void DebugHUDDraw(sf::RenderWindow &window);

private:
    sf::RenderWindow &mWindow;
    const Level &mLevel;
    const UI &mUi;
    SpriteGroup mSortedSpriteGroup;
    sf::View mView;
};
