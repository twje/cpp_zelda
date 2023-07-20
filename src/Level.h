#pragma once

#include <sstream>

// Core
#include "Core/SpriteGroup.h"
#include "Core/Debug.h"

// Game
#include "Settings.h"
#include "Tile.h"
#include "Player.h"

class Level
{
public:
    Level();

    void Update();
    const Player &GetPlayer() const { return *mPlayer; }
    const SpriteGroup &GetVisibleSpriteGroup() const { return mVisibleSprites; }

private:
    void CreateMap();

private:
    SpriteGroup mVisibleSprites;
    SpriteGroup mObstacleSprites;
    std::shared_ptr<Player> mPlayer;
};