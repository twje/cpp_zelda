#include "Tile.h"
#include "Sprite.h"
#include "Rect.h"

Tile::Tile(sf::Vector2f position)
    : Sprite(),
      mTexture(std::make_unique<sf::Texture>())
{
    assert(mTexture->loadFromFile("../graphics/test/rock.png"));
    mRect = Util::GetRect(mTexture->getSize(), position, Util::RectCorner::TOP_LEFT);
}

const sf::Texture &Tile::GetTexture() const
{
    return *mTexture;
}

Util::FloatRect Tile::GetRect() const
{
    return mRect;
}
