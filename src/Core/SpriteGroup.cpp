
#include "SpriteGroup.h"

void SpriteGroup::YSortSprites()
{
    std::sort(mSprites.begin(), mSprites.end(), [](const std::shared_ptr<Sprite> &sprite1, const std::shared_ptr<Sprite> &sprite2)
              { return sprite1->GetRect().GetCenterY() < sprite2->GetRect().GetCenterY(); });
}

void SpriteGroup::Update()
{
    for (const auto &internalSprite : mSprites)
    {
        internalSprite->Update();
    }
}