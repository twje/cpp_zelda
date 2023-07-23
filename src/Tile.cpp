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
    mTextureRegion = sf::IntRect(sf::Vector2i(position), sf::Vector2i(mTexture.getSize()));
    if (spriteType == SpriteType::OBJECT)
    {
        mRect = FloatRect(position, sf::Vector2f(mTexture.getSize()));
        mRect.AnchorPosition(Anchor::TOP_LEFT, sf::Vector2f(position.x, position.y - TILESIZE));
    }
    else
    {
        mRect = FloatRect(position, sf::Vector2f(mTexture.getSize()));
    }
    mHitbox = mRect.Inflate(0, -10);
}
