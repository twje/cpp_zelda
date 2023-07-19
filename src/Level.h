#pragma once

#include <sstream>

#include "Settings.h"
#include "SpriteGroup.h"
#include "Tile.h"
#include "Player.h"
#include "Debug.h"

class Level
{
public:
    Level()
    {
        CreateMap();
    }

    void Update()
    {
        mVisibleSprites.Update();
    }

    const Player &GetPlayer() const { return *mPlayer; }
    const SpriteGroup &GetVisibleSpriteGroup() const { return mVisibleSprites; }

private:
    void CreateMap();

private:
    SpriteGroup mVisibleSprites;
    SpriteGroup mObstacleSprites;
    std::shared_ptr<Player> mPlayer;
};