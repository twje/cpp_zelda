#pragma once

// Game
#include "Core/Sprite.h"
#include "Constants.h"

class Tile : public Sprite
{
public:
    Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture);
    sf::FloatRect GetHitbox() const override { return mHitBox; }

private:
    SpriteType mSpriteType;
    sf::FloatRect mHitBox;
};