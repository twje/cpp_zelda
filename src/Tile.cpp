// Core
#include "Core/Sprite.h"
#include "Core/RectUtils.h"

// Game
#include "Tile.h"
#include "Settings.h"
#include "Support.h"

Tile::Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture)
    : Sprite(texture),
      mSpriteType(spriteType)
{
    setPosition(position);
    if (spriteType == SpriteType::OBJECT)
    {
        // 2x the height of normal tiles
        move(sf::Vector2f(0, -TILESIZE));
    }
    mHitBox = InflateRect(GetGlobalBounds(), 0, -10);
}