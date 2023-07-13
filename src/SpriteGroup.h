#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Sprite.h"

class SpriteGroup
{
public:
    void Add(const std::shared_ptr<Sprite> &sprite);

    void Draw(sf::RenderWindow &window)
    {
        for (const auto &internalSprite : mSprites)
        {
            sf::FloatRect rect = internalSprite->GetRect();
            sf::Sprite sprite(internalSprite->GetTexture());
            sprite.setPosition(rect.getPosition());
            window.draw(sprite);
        }
    }

private:
    std::vector<std::shared_ptr<Sprite>> mSprites;
};
