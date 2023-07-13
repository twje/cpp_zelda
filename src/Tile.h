#pragma once

#include "Sprite.h"

class Tile : public Sprite
{
public:
    Tile();

public:
    const sf::Texture &GetTexture() const override;
    sf::FloatRect GetRect() const override;

private:
    std::unique_ptr<sf::Texture> mTexture;
};