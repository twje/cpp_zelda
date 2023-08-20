#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Settings.h"
#include "Core/Sprite.h"

class Entity : public Sprite
{
public:
    Entity(const Group &obstacles);

    void Move(const sf::Time &timestamp, float speed);
    void Collision(Direction direction);

    // Helper Methods
    bool IsMovingRight() { return mDirection.x > 0; }
    bool IsMovingLeft() { return mDirection.x < 0; }
    bool IsMovingUp() { return mDirection.y < 0; }
    bool IsMovingDown() { return mDirection.y > 0; }

protected:
    const Group &mObstacles;
    sf::Vector2f mDirection;
    sf::FloatRect mHitBox;
};