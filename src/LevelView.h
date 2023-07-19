#pragma once

#include <SFML/Graphics.hpp>

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
    void DebugDrawPlayer(sf::RenderWindow &window);

private:
    const Level &mLevel;
    sf::Vector2f mCameraOffset;
};
