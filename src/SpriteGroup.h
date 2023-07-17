#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Sprite.h"

class SpriteGroup
{
public:
    void Add(const std::shared_ptr<Sprite> &sprite);

    const std::vector<std::shared_ptr<Sprite>> &GetSprites() const
    {
        return mSprites;
    }

    void Update()
    {
        for (const auto &internalSprite : mSprites)
        {
            internalSprite->Update();
        }
    }

    void Draw(sf::RenderWindow &window)
    {
        for (const auto &internalSprite : mSprites)
        {
            Util::FloatRect rect = internalSprite->GetRect();
            sf::Sprite sprite(internalSprite->GetTexture());
            sprite.setPosition(sf::Vector2f(rect.GetX(), rect.GetY()));
            window.draw(sprite);
        }
    }

private:
    std::vector<std::shared_ptr<Sprite>> mSprites;
};
