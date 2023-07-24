
#include "SpriteGroup.h"

void SpriteGroup::YSortSprites()
{
    std::sort(mSprites.begin(), mSprites.end(), [](const std::shared_ptr<Sprite> &sprite1, const std::shared_ptr<Sprite> &sprite2)
              { return sprite1->GetSpriteData().GetBoundingBox().GetCenterY() < sprite2->GetSpriteData().GetBoundingBox().GetCenterY(); });
}

void SpriteGroup::Update(const sf::Time &timestamp)
{
    for (const auto &internalSprite : mSprites)
    {
        internalSprite->Update(timestamp);
    }
}