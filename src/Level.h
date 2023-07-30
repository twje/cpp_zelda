#pragma once

#include <sstream>

#include <map>
#include <memory>

// Core
#include "Core/SpriteGroup.h"
#include "Core/Debug.h"

// Game
#include "Settings.h"
#include "Support.h"
#include "Tile.h"
#include "Player.h"

// Game
#include "Weapon.h"

class Level
{
public:
    Level();

    void Update(const sf::Time &timestamp);
    const Player &GetPlayer() const { return *mPlayer; }
    const SpriteGroup &GetVisibleSpriteGroup() const { return mVisibleSprites; }
    const sf::Texture &GetFloorTexture() const { return *mFloor; }

private:
    void CreateMap();
    void CreateAttack();
    void DestroyAttack();

private:
    Ref<Player> mPlayer;
    Ref<Weapon> mCurrentAttack;
    SpriteGroup mVisibleSprites;
    SpriteGroup mObstacleSprites;
    TextureMap mGraphics;
    TexturePtr mInvisibleBlock;
    TexturePtr mFloor;
};