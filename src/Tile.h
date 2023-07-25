#pragma once

// Game
#include "Core/Sprite.h"
#include "Constants.h"

class Tile : public Sprite
{
public:
    Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture);

public:
    void Draw(sf::RenderWindow &window) override;
    const SpriteDataView &GetSpriteData() const { return mData.GetDataView(); }

private:
    SpriteData mData;
    SpriteType mSpriteType;
};