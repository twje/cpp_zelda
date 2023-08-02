
#include "Core/Group.h"

// Game
#include "GameObject.h"

void Group::Add(const std::shared_ptr<GameObject> &sprite)
{
    mGameObjects.emplace_back(sprite);
    sprite->RegisterGroup(this);
};

void Group::YSortGameObjects()
{
    std::sort(mGameObjects.begin(), mGameObjects.end(), [](const std::shared_ptr<GameObject> &sprite1, const std::shared_ptr<GameObject> &sprite2)
              { return sprite1->GetCenter().y < sprite2->GetCenter().y; });
}

void Group::Update(const sf::Time &timestamp)
{
    for (const auto &internalSprite : mGameObjects)
    {
        internalSprite->Update(timestamp);
    }
}

void Group::RemoveSprite(const GameObject &sprite)
{
    mGameObjects.erase(std::remove_if(mGameObjects.begin(), mGameObjects.end(), [&sprite](const std::shared_ptr<GameObject> &element)
                                      { return element.get() == &sprite; }),
                       mGameObjects.end());
}