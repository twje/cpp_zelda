#include "Player.h"
#include "Sprite.h"
#include "Rect.h"

Player::Player(sf::Vector2f position)
    : Sprite(),
      mTexture(std::make_unique<sf::Texture>())
{
    assert(mTexture->loadFromFile("../graphics/test/player.png"));
    mRect = Util::GetRect(mTexture->getSize(), position, Util::RectCorner::TOP_LEFT);
}

const sf::Texture &Player::GetTexture() const
{
    return *mTexture;
}

sf::FloatRect Player::GetRect() const
{
    return mRect;
}
