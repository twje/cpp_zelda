#pragma once

#include "Sprite.h"

class Tile : public Sprite
{
public:
    Tile(sf::Vector2f position);

public:
    const sf::Texture &GetTexture() const override;
    sf::FloatRect GetRect() const override;

private:
    std::unique_ptr<sf::Texture> mTexture;
    sf::FloatRect mRect;
};