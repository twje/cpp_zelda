#pragma once

#include "Sprite.h"

class Player : public Sprite
{
public:
    Player(sf::Vector2f position);

public:
    const sf::Texture &GetTexture() const override;
    sf::FloatRect GetRect() const override;

private:
    std::unique_ptr<sf::Texture> mTexture;
    sf::FloatRect mRect;
};