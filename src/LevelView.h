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
    LevelView(const Level &view);

    void Draw(sf::RenderWindow &window);

private:
    sf::Vector2f GetFixedCenterCameraOffset(sf::RenderWindow &window, const Sprite &relativeTo);
    void DebugDraw(sf::RenderWindow &window);
    void DebugDrawPlayer(sf::RenderWindow &window);
    void DebugHitbox(sf::RenderWindow &window);

private:
    const Level &mLevel;
    SpriteGroup mSortedSpriteGroup;
    sf::Vector2f mCameraOffset;
};
