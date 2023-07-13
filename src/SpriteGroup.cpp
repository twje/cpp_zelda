
#include "SpriteGroup.h"

void SpriteGroup::Add(const std::shared_ptr<Sprite> &sprite)
{
    mSprites.push_back(sprite);
}