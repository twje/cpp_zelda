#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

// Forward declared class
class Sprite;

class SpriteGroup
{
public:
    using SpriteList = std::vector<std::shared_ptr<Sprite>>;

    void Add(const std::shared_ptr<Sprite> &sprite);
    const SpriteList &GetSprites() const { return mSprites; }
    void YSortSprites();
    void Update(const sf::Time &timestamp);
    void RemoveSprite(const Sprite &sprite);

private:
    SpriteList mSprites;
};
