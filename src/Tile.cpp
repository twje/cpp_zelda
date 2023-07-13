#include "Tile.h"
#include "Sprite.h"

Tile::Tile()
    : Sprite(),
      mTexture(std::make_unique<sf::Texture>())
{
    assert(mTexture->loadFromFile("../graphics/test/rock.png"));
}

const sf::Texture &Tile::GetTexture() const
{
    return *mTexture;
}

sf::FloatRect Tile::GetRect() const
{
    return sf::FloatRect();
}
