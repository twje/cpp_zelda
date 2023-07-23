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
    sf::IntRect GetTextureRegion() const { return mTextureRegion; }
    FloatRect GetRect() const override { return mRect; };
    FloatRect GetHitbox() const override { return mHitbox; };

private:
    sf::Texture &mTexture;
    sf::IntRect mTextureRegion;
    FloatRect mRect;
    FloatRect mHitbox;
    SpriteType mSpriteType;
};