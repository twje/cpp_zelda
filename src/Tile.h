#pragma once

// Game
#include "Core/Sprite.h"
#include "Constants.h"

class Tile : public Sprite
{
public:
    Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture);

public:
    const sf::Texture &GetTexture() const override;
    FloatRect GetRect() const override;

private:
    sf::Texture &mTexture;
    FloatRect mRect;
    SpriteType mSpriteType;
};