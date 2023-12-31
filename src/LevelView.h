#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Core/Layer.h"
#include "Core/Group.h"

// Forward declarations
class Level;
class Sprite;

class LevelView : public Layer
{
public:
    LevelView(const Level &level);

    void Draw(sf::RenderWindow &window) override;
    void OnWindowResize(sf::Vector2u size) override;

private:
    void DebugWorldDraw(sf::RenderWindow &window);
    void DebugDrawPlayer(sf::RenderWindow &window);
    void DebugHitbox(sf::RenderWindow &window);

private:
    const Level &mLevel;
    Group mSortedSpriteGroup;
    sf::View mView;
};
