#pragma once

#include "Core/TextureManager.h"
#include "Core/Sprite.h"
#include "Constants.h"

class Weapon : public Sprite
{
public:
    Weapon(sf::Vector2f position)
        : Sprite()
    {
    }

    sf::FloatRect GetHitbox() const override { return mHitBox; }

private:
    void LoadAssets()
    {
        TextureManager &textureManager = TextureManager::GetInstance();
    }

private:
    sf::FloatRect mHitBox;
};
