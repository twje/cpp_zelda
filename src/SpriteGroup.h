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

        for (const auto &sprite : mSprites)
        {
            sf::Sprite foo(sprite->GetTexture());
            window.draw(foo);
        }
    }

private:
    std::vector<std::shared_ptr<Sprite>> mSprites;
};
