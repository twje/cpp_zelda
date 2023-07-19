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

    void YSortSprites()
    {
        std::sort(mSprites.begin(), mSprites.end(), [](const std::shared_ptr<Sprite> &sprite1, const std::shared_ptr<Sprite> &sprite2)
                  { return sprite1->GetRect().GetCenterY() < sprite2->GetRect().GetCenterY(); });
    }

    void Update()
    {
        for (const auto &internalSprite : mSprites)
        {
            internalSprite->Update();
        }
    }

private:
    std::vector<std::shared_ptr<Sprite>> mSprites;
};
