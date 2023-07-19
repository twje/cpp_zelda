#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Sprite.h"

class SpriteGroup
{
public:
    using SpriteList = std::vector<std::shared_ptr<Sprite>>;

    void Add(const std::shared_ptr<Sprite> &sprite) { mSprites.push_back(sprite); };
    const SpriteList &GetSprites() const { return mSprites; }
    void YSortSprites();
    void Update();

private:
    SpriteList mSprites;
};
