
#include "Core/Group.h"

// Game
#include "GameObject.h"

void Group::Add(const std::shared_ptr<GameObject> &sprite)
{
    mSprites.emplace_back(sprite);
    sprite->RegisterGroup(this);
};

void Group::YSortSprites()
{
    std::sort(mSprites.begin(), mSprites.end(), [](const std::shared_ptr<GameObject> &sprite1, const std::shared_ptr<GameObject> &sprite2)
              { return sprite1->GetCenter().y < sprite2->GetCenter().y; });
}

void Group::Update(const sf::Time &timestamp)
{
    for (const auto &internalSprite : mSprites)
    {
        internalSprite->Update(timestamp);
    }
}

void Group::RemoveSprite(const GameObject &sprite)
{
    mSprites.erase(std::remove_if(mSprites.begin(), mSprites.end(), [&sprite](const std::shared_ptr<GameObject> &element)
                                  { return element.get() == &sprite; }),
                   mSprites.end());
}