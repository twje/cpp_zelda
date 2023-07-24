#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Core/SpriteGroup.h"

// Forward declarations
class Level;
class Sprite;

class LevelView
{
public:
    LevelView(sf::RenderWindow &window, const Level &view);

    void Draw(sf::RenderWindow &window);

private:
    void DebugDraw(sf::RenderWindow &window);
    void DebugDrawPlayer(sf::RenderWindow &window);
    void DebugHitbox(sf::RenderWindow &window);

private:
    sf::RenderWindow &mWindow;
    const Level &mLevel;
    SpriteGroup mSortedSpriteGroup;
    sf::View mView;
};
