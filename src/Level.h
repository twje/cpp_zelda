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
#include "Weapon.h"
#include "LevelView.h"
#include "UI.h"

class Level : public Layer
{
public:
    Level();

    void Update(const sf::Time &timestamp) override;
    void Draw(sf::RenderWindow &window) override;
    void OnWindowResize(sf::Vector2u size) override;

    // Getters
    const Player &GetPlayer() const { return *mPlayer; }
    const Group &GetVisibleSpriteGroup() const { return mVisibleSpriteGroup; }
    const sf::Texture &GetFloorTexture() const { return *mFloor; }

private:
    void CreateMap();

    // Factory methods
    static std::shared_ptr<Player> CreatePlayer(Level *level, float x, float y, const Group &obstacles);

    // Callbacks
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
    std::unique_ptr<LevelView> mLevelView;
    std::unique_ptr<UI> mUI;
};