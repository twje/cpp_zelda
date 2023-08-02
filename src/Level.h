#pragma once

#include <sstream>

#include <map>
#include <memory>

// Core
#include "Core/Layer.h"
#include "Core/Group.h"
#include "Core/Debug.h"

// Game
#include "Settings.h"
#include "Support.h"
#include "Tile.h"
#include "Player.h"

// Game
#include "Weapon.h"

class Level : public Layer
{
public:
    Level();

    void Update(const sf::Time &timestamp) override;
    const Player &GetPlayer() const { return *mPlayer; }
    const Group &GetVisibleSpriteGroup() const { return mVisibleSpriteGroup; }
    const sf::Texture &GetFloorTexture() const { return *mFloor; }

private:
    void CreateMap();
    void CreateAttack();
    void DestroyAttack();

private:
    Ref<Player> mPlayer;
    Ref<Weapon> mCurrentAttack;
    Group mVisibleSpriteGroup;
    Group mObstacleSpriteGroup;
    TextureMap mGraphics;
    TexturePtr mInvisibleBlock;
    TexturePtr mFloor;
};