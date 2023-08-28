#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Core/Iterator.h"

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

    // Iterator
    Iterator<GameObjectVector> begin() { return Iterator<GameObjectVector>(mGameObjects.begin()); }
    Iterator<GameObjectVector> end() { return Iterator<GameObjectVector>(mGameObjects.end()); }

private:
    GameObjectVector mGameObjects;
};
