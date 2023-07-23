#pragma once

// Game
#include "Core/Sprite.h"
#include "Constants.h"

class Tile : public Sprite
{
public:
    Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture);

public:
    const sf::Texture &GetTexture() const override { return mTexture; }
    FloatRect GetRect() const override { return mRect; };
    FloatRect GetHitbox() const override { return mHitbox; };

private:
    sf::Texture &mTexture;
    FloatRect mRect;
    FloatRect mHitbox;
    SpriteType mSpriteType;
};