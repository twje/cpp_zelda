// Core
#include "Core/Sprite.h"
#include "Core/RectUtils.h"

// Game
#include "Settings.h"
#include "Tile.h"
#include "Support.h"

Tile::Tile(sf::Vector2f position, SpriteType spriteType, const std::shared_ptr<sf::Texture> &texture)
    : Sprite(texture),
      mSpriteType(spriteType)
{
    SetPosition(position);
    if (spriteType == SpriteType::OBJECT)
    {
        // 2x the height of normal tiles
        Move(sf::Vector2f(0, -TILESIZE));
    }
    mHitBox = InflateRect(GetGlobalBounds(), 0, -10);
}