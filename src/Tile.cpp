// Core
#include "Core/Sprite.h"
#include "Core/Rect.h"

// Game
#include "Tile.h"
#include "Settings.h"

Tile::Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture)
    : Sprite(),
      mTexture(texture)
{
    if (spriteType == SpriteType::OBJECT)
    {
        mRect = FloatRect(position, sf::Vector2f(mTexture.getSize()));
        mRect.AnchorPosition(Anchor::TOP_LEFT, sf::Vector2f(position.x, position.y - TILESIZE));
    }
    else
    {
        mRect = FloatRect(position, sf::Vector2f(mTexture.getSize()));
    }
}

const sf::Texture &Tile::GetTexture() const
{
    return mTexture;
}

FloatRect Tile::GetRect() const
{
    return mRect;
}
