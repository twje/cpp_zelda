
#include "SpriteGroup.h"

// Game
#include "Sprite.h"

void SpriteGroup::Add(const std::shared_ptr<Sprite> &sprite)
{
    mSprites.emplace_back(sprite);
    sprite->mSpriteGroups.emplace_back(this);
};

void SpriteGroup::YSortSprites()
{
    std::sort(mSprites.begin(), mSprites.end(), [](const std::shared_ptr<Sprite> &sprite1, const std::shared_ptr<Sprite> &sprite2)
              { return sprite1->GetCenter().y < sprite2->GetCenter().y; });
}

void SpriteGroup::Update(const sf::Time &timestamp)
{
    for (const auto &internalSprite : mSprites)
    {
        internalSprite->Update(timestamp);
    }
}

void SpriteGroup::RemoveSprite(const Sprite &sprite)
{
    mSprites.erase(std::remove_if(mSprites.begin(), mSprites.end(), [&sprite](const std::shared_ptr<Sprite> &element)
                                  { return element.get() == &sprite; }),
                   mSprites.end());
}