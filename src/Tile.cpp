// Core
#include "Core/Sprite.h"
#include "Core/Rect.h"

// Game
#include "Tile.h"
#include "Settings.h"

Tile::Tile(sf::Vector2f position, SpriteType spriteType, sf::Texture &texture)
    : Sprite()
{
    mData.SetTexture(&texture);
    mData.SetTextureRegion(sf::IntRect(sf::Vector2i(), sf::Vector2i(mData.GetTexture().getSize())));
    mData.SetBoundingBox(FloatRect(position, sf::Vector2f(mData.GetTexture().getSize())));

    if (spriteType == SpriteType::OBJECT)
    {
        mData.GetMutableBoundingBox().AnchorPosition(Anchor::TOP_LEFT, sf::Vector2f(position.x, position.y - TILESIZE));
    }
    mData.SetHitBox(mData.GetBoundingBox().Inflate(0, -10));
}
