#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

// Forward declared class
class GameObject;

class Group
{
public:
    using GameObjectVector = std::vector<std::shared_ptr<GameObject>>;

    void Add(const std::shared_ptr<GameObject> &sprite);
    const GameObjectVector &GetGameObjects() const { return mGameObjects; }
    GameObjectVector &GetGameObjects() { return mGameObjects; }
    void YSortGameObjects();
    void Update(const sf::Time &timestamp);
    void RemoveSprite(const GameObject &sprite);

private:
    GameObjectVector mGameObjects;
};
