#pragma once

// Game
#include "Core/Sprite.h"

class Tile : public Sprite
{
public:
    Tile(sf::Vector2f position, SpriteType spriteType, const std::shared_ptr<sf::Texture> &texture);
    sf::FloatRect GetHitbox() const override { return mHitBox; }

private:
    SpriteType mSpriteType;
    sf::FloatRect mHitBox;
};