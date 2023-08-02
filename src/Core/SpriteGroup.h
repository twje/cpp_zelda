#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

// Forward declared class
class GameObject;

class SpriteGroup
{
public:
    using SpriteList = std::vector<std::shared_ptr<GameObject>>;

    void Add(const std::shared_ptr<GameObject> &sprite);
    const SpriteList &GetSprites() const { return mSprites; }
    void YSortSprites();
    void Update(const sf::Time &timestamp);
    void RemoveSprite(const GameObject &sprite);

private:
    SpriteList mSprites;
};
