#include "Tile.h"
#include "Sprite.h"
#include "Rect.h"

Tile::Tile(sf::Vector2f position)
    : Sprite(),
      mTexture(std::make_unique<sf::Texture>())
{
    assert(mTexture->loadFromFile("../graphics/test/rock.png"));
    mRect = FloatRect(position, sf::Vector2f(mTexture->getSize()));
}

const sf::Texture &Tile::GetTexture() const
{
    return *mTexture;
}

FloatRect Tile::GetRect() const
{
    return mRect;
}
